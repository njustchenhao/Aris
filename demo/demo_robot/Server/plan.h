#ifndef PLAN_H
#define PLAN_H
#include <aris.h>

namespace robot
{

    //for enable disable and home
    auto basicParse(aris::server::ControlServer &cs, const std::string &cmd, const std::map<std::string, std::string> &params, aris::core::Msg &msg_out)->void;

    //for basic gait command parser
    auto basicGaitParse(aris::server::ControlServer &cs, const std::string &cmd, const std::map<std::string, std::string> &params, aris::core::Msg &msg_out)->void;

    //switch on or off the log function
    auto logParse(aris::server::ControlServer &cs,const std::string &cmd, const std::map<std::string, std::string> &params, aris::core::Msg &msg_out)->void;

    //get the help about command or param
    auto helpParse(aris::server::ControlServer &cs,const std::string &cmd, const std::map<std::string, std::string> &params, aris::core::Msg &msg_out)->void;

    //the robot can recover to a default pose by using 'rc' command when it has found home. the pose can be changed in the RecoverParam
    struct RecoverParam final : public aris::server::GaitParamBase
    {
        int total_count_{ 10000 };//the total time(ms)
        double target_pin_[3]{0,PI/2, -PI/2};//the angle of axis
        double target_pee_[3]{1,1,0};//the default pose
    };
    auto recoverParse(aris::server::ControlServer &cs, const std::string &cmd, const std::map<std::string, std::string> &params, aris::core::Msg &msg_out)->void;
    auto recoverGait(aris::dynamic::Model &model, const aris::dynamic::PlanParamBase &param_in)->int;

    //move the robot to specify pose or move the specify axis of robot
    struct MoveParam final: public aris::server::GaitParamBase
    {
        int total_count_{10000};
        double target_x_{0}, target_y_{0.435},   target_A_{0};
        double round_{0};
        double a1_{0},a2_{0},a3_{0};
        double kp_{0};
        int mode_{0};//1:pee, 2:pin, 3:pins
        };
    auto moveParse(aris::server::ControlServer &cs, const std::string &cmd, const std::map<std::string, std::string> &params, aris::core::Msg &msg_out)->void;
    auto moveGait(aris::dynamic::Model &model, const aris::dynamic::PlanParamBase &param_in)->int;

    }


#endif

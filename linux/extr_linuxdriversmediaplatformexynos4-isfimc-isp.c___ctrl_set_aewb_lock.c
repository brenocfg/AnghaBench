#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl {int val; } ;
struct TYPE_7__ {int cmd; void* target; } ;
struct isp_param {TYPE_3__ aa; } ;
struct TYPE_8__ {int ae_lock_state; int awb_lock_state; } ;
struct fimc_is {TYPE_4__ af; TYPE_2__* is_p_region; } ;
struct TYPE_5__ {struct isp_param isp; } ;
struct TYPE_6__ {TYPE_1__ parameter; } ;

/* Variables and functions */
 int ISP_AA_COMMAND_START ; 
 int ISP_AA_COMMAND_STOP ; 
 void* ISP_AA_TARGET_AE ; 
 int /*<<< orphan*/  PARAM_ISP_AA ; 
 int V4L2_LOCK_EXPOSURE ; 
 int V4L2_LOCK_WHITE_BALANCE ; 
 int fimc_is_itf_s_param (struct fimc_is*,int) ; 
 int /*<<< orphan*/  fimc_is_set_param_bit (struct fimc_is*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int __ctrl_set_aewb_lock(struct fimc_is *is,
				      struct v4l2_ctrl *ctrl)
{
	bool awb_lock = ctrl->val & V4L2_LOCK_WHITE_BALANCE;
	bool ae_lock = ctrl->val & V4L2_LOCK_EXPOSURE;
	struct isp_param *isp = &is->is_p_region->parameter.isp;
	int cmd, ret;

	cmd = ae_lock ? ISP_AA_COMMAND_STOP : ISP_AA_COMMAND_START;
	isp->aa.cmd = cmd;
	isp->aa.target = ISP_AA_TARGET_AE;
	fimc_is_set_param_bit(is, PARAM_ISP_AA);
	is->af.ae_lock_state = ae_lock;
	wmb();

	ret = fimc_is_itf_s_param(is, false);
	if (ret < 0)
		return ret;

	cmd = awb_lock ? ISP_AA_COMMAND_STOP : ISP_AA_COMMAND_START;
	isp->aa.cmd = cmd;
	isp->aa.target = ISP_AA_TARGET_AE;
	fimc_is_set_param_bit(is, PARAM_ISP_AA);
	is->af.awb_lock_state = awb_lock;
	wmb();

	return fimc_is_itf_s_param(is, false);
}
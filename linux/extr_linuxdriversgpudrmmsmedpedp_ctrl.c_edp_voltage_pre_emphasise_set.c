#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct edp_ctrl {scalar_t__ p_level; scalar_t__ v_level; int /*<<< orphan*/  phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,scalar_t__,scalar_t__) ; 
 int EINVAL ; 
 int edp_lane_set_write (struct edp_ctrl*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  msm_edp_phy_vm_pe_cfg (int /*<<< orphan*/ ,int,int) ; 
 int** vm_pre_emphasis ; 
 int** vm_voltage_swing ; 

__attribute__((used)) static int edp_voltage_pre_emphasise_set(struct edp_ctrl *ctrl)
{
	u32 value0;
	u32 value1;

	DBG("v=%d p=%d", ctrl->v_level, ctrl->p_level);

	value0 = vm_pre_emphasis[(int)(ctrl->v_level)][(int)(ctrl->p_level)];
	value1 = vm_voltage_swing[(int)(ctrl->v_level)][(int)(ctrl->p_level)];

	/* Configure host and panel only if both values are allowed */
	if (value0 != 0xFF && value1 != 0xFF) {
		msm_edp_phy_vm_pe_cfg(ctrl->phy, value0, value1);
		return edp_lane_set_write(ctrl, ctrl->v_level, ctrl->p_level);
	}

	return -EINVAL;
}
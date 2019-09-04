#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bnx2x_func_set_timesync_params {int drift_adjust_value; int drift_adjust_period; int /*<<< orphan*/  add_sub_drift_adjust_value; int /*<<< orphan*/  offset_cmd; int /*<<< orphan*/  drift_adjust_cmd; } ;
struct TYPE_2__ {struct bnx2x_func_set_timesync_params set_timesync; } ;
struct bnx2x_func_state_params {int /*<<< orphan*/  cmd; int /*<<< orphan*/ * f_obj; int /*<<< orphan*/  ramrod_flags; TYPE_1__ params; int /*<<< orphan*/ * member_0; } ;
struct bnx2x {int /*<<< orphan*/  func_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_F_CMD_SET_TIMESYNC ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int /*<<< orphan*/  RAMROD_RETRY ; 
 int /*<<< orphan*/  TS_ADD_VALUE ; 
 int /*<<< orphan*/  TS_DRIFT_ADJUST_SET ; 
 int /*<<< orphan*/  TS_OFFSET_KEEP ; 
 int /*<<< orphan*/  TS_SUB_VALUE ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bnx2x_func_state_change (struct bnx2x*,struct bnx2x_func_state_params*) ; 

__attribute__((used)) static int bnx2x_send_update_drift_ramrod(struct bnx2x *bp, int drift_dir,
					  int best_val, int best_period)
{
	struct bnx2x_func_state_params func_params = {NULL};
	struct bnx2x_func_set_timesync_params *set_timesync_params =
		&func_params.params.set_timesync;

	/* Prepare parameters for function state transitions */
	__set_bit(RAMROD_COMP_WAIT, &func_params.ramrod_flags);
	__set_bit(RAMROD_RETRY, &func_params.ramrod_flags);

	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_SET_TIMESYNC;

	/* Function parameters */
	set_timesync_params->drift_adjust_cmd = TS_DRIFT_ADJUST_SET;
	set_timesync_params->offset_cmd = TS_OFFSET_KEEP;
	set_timesync_params->add_sub_drift_adjust_value =
		drift_dir ? TS_ADD_VALUE : TS_SUB_VALUE;
	set_timesync_params->drift_adjust_value = best_val;
	set_timesync_params->drift_adjust_period = best_period;

	return bnx2x_func_state_change(bp, &func_params);
}
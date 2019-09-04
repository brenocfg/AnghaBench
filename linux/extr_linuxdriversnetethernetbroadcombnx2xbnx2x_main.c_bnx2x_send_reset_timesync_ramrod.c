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
struct bnx2x_func_set_timesync_params {int /*<<< orphan*/  offset_cmd; int /*<<< orphan*/  drift_adjust_cmd; } ;
struct TYPE_2__ {struct bnx2x_func_set_timesync_params set_timesync; } ;
struct bnx2x_func_state_params {int /*<<< orphan*/  cmd; int /*<<< orphan*/ * f_obj; int /*<<< orphan*/  ramrod_flags; TYPE_1__ params; int /*<<< orphan*/ * member_0; } ;
struct bnx2x {int /*<<< orphan*/  func_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_F_CMD_SET_TIMESYNC ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int /*<<< orphan*/  RAMROD_RETRY ; 
 int /*<<< orphan*/  TS_DRIFT_ADJUST_RESET ; 
 int /*<<< orphan*/  TS_OFFSET_KEEP ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bnx2x_func_state_change (struct bnx2x*,struct bnx2x_func_state_params*) ; 

__attribute__((used)) static int bnx2x_send_reset_timesync_ramrod(struct bnx2x *bp)
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
	set_timesync_params->drift_adjust_cmd = TS_DRIFT_ADJUST_RESET;
	set_timesync_params->offset_cmd = TS_OFFSET_KEEP;

	return bnx2x_func_state_change(bp, &func_params);
}
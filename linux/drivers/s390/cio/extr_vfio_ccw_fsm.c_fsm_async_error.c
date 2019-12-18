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
struct vfio_ccw_private {int /*<<< orphan*/  state; struct ccw_cmd_region* cmd_region; } ;
struct ccw_cmd_region {scalar_t__ command; int /*<<< orphan*/  ret_code; } ;
typedef  enum vfio_ccw_event { ____Placeholder_vfio_ccw_event } vfio_ccw_event ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ VFIO_CCW_ASYNC_CMD_CSCH ; 
 scalar_t__ VFIO_CCW_ASYNC_CMD_HSCH ; 
 int /*<<< orphan*/  pr_err (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsm_async_error(struct vfio_ccw_private *private,
			    enum vfio_ccw_event event)
{
	struct ccw_cmd_region *cmd_region = private->cmd_region;

	pr_err("vfio-ccw: FSM: %s request from state:%d\n",
	       cmd_region->command == VFIO_CCW_ASYNC_CMD_HSCH ? "halt" :
	       cmd_region->command == VFIO_CCW_ASYNC_CMD_CSCH ? "clear" :
	       "<unknown>", private->state);
	cmd_region->ret_code = -EIO;
}
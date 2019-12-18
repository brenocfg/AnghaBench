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
struct vfio_ccw_private {struct ccw_cmd_region* cmd_region; } ;
struct ccw_cmd_region {int command; int /*<<< orphan*/  ret_code; } ;
typedef  enum vfio_ccw_event { ____Placeholder_vfio_ccw_event } vfio_ccw_event ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  VFIO_CCW_ASYNC_CMD_CSCH 129 
#define  VFIO_CCW_ASYNC_CMD_HSCH 128 
 int /*<<< orphan*/  fsm_do_clear (struct vfio_ccw_private*) ; 
 int /*<<< orphan*/  fsm_do_halt (struct vfio_ccw_private*) ; 

__attribute__((used)) static void fsm_async_request(struct vfio_ccw_private *private,
			      enum vfio_ccw_event event)
{
	struct ccw_cmd_region *cmd_region = private->cmd_region;

	switch (cmd_region->command) {
	case VFIO_CCW_ASYNC_CMD_HSCH:
		cmd_region->ret_code = fsm_do_halt(private);
		break;
	case VFIO_CCW_ASYNC_CMD_CSCH:
		cmd_region->ret_code = fsm_do_clear(private);
		break;
	default:
		/* should not happen? */
		cmd_region->ret_code = -EINVAL;
	}
}
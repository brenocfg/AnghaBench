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
struct subchannel {int opm; int lpm; int /*<<< orphan*/  ssd_info; } ;
struct chp_link {int dummy; } ;
struct ccw_device {TYPE_1__* private; } ;
struct TYPE_2__ {int path_gone_mask; int path_new_mask; } ;

/* Variables and functions */
#define  CHP_OFFLINE 131 
#define  CHP_ONLINE 130 
#define  CHP_VARY_OFF 129 
#define  CHP_VARY_ON 128 
 int ENODEV ; 
 int chp_ssd_get_mask (int /*<<< orphan*/ *,struct chp_link*) ; 
 int /*<<< orphan*/  cio_update_schib (struct subchannel*) ; 
 int /*<<< orphan*/  io_subchannel_terminate_path (struct subchannel*,int) ; 
 int /*<<< orphan*/  io_subchannel_verify (struct subchannel*) ; 
 struct ccw_device* sch_get_cdev (struct subchannel*) ; 

__attribute__((used)) static int io_subchannel_chp_event(struct subchannel *sch,
				   struct chp_link *link, int event)
{
	struct ccw_device *cdev = sch_get_cdev(sch);
	int mask;

	mask = chp_ssd_get_mask(&sch->ssd_info, link);
	if (!mask)
		return 0;
	switch (event) {
	case CHP_VARY_OFF:
		sch->opm &= ~mask;
		sch->lpm &= ~mask;
		if (cdev)
			cdev->private->path_gone_mask |= mask;
		io_subchannel_terminate_path(sch, mask);
		break;
	case CHP_VARY_ON:
		sch->opm |= mask;
		sch->lpm |= mask;
		if (cdev)
			cdev->private->path_new_mask |= mask;
		io_subchannel_verify(sch);
		break;
	case CHP_OFFLINE:
		if (cio_update_schib(sch))
			return -ENODEV;
		if (cdev)
			cdev->private->path_gone_mask |= mask;
		io_subchannel_terminate_path(sch, mask);
		break;
	case CHP_ONLINE:
		if (cio_update_schib(sch))
			return -ENODEV;
		sch->lpm |= mask & sch->opm;
		if (cdev)
			cdev->private->path_new_mask |= mask;
		io_subchannel_verify(sch);
		break;
	}
	return 0;
}
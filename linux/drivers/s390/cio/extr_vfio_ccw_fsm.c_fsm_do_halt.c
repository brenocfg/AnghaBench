#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vfio_ccw_private {struct subchannel* sch; } ;
struct TYPE_4__ {int /*<<< orphan*/  actl; } ;
struct TYPE_5__ {TYPE_1__ cmd; } ;
struct TYPE_6__ {TYPE_2__ scsw; } ;
struct subchannel {int /*<<< orphan*/  lock; TYPE_3__ schib; int /*<<< orphan*/  schid; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  ccode ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  SCSW_ACTL_HALT_PEND ; 
 int /*<<< orphan*/  VFIO_CCW_HEX_EVENT (int,int*,int) ; 
 int /*<<< orphan*/  VFIO_CCW_TRACE_EVENT (int,char*) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int hsch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int fsm_do_halt(struct vfio_ccw_private *private)
{
	struct subchannel *sch;
	unsigned long flags;
	int ccode;
	int ret;

	sch = private->sch;

	spin_lock_irqsave(sch->lock, flags);

	VFIO_CCW_TRACE_EVENT(2, "haltIO");
	VFIO_CCW_TRACE_EVENT(2, dev_name(&sch->dev));

	/* Issue "Halt Subchannel" */
	ccode = hsch(sch->schid);

	VFIO_CCW_HEX_EVENT(2, &ccode, sizeof(ccode));

	switch (ccode) {
	case 0:
		/*
		 * Initialize device status information
		 */
		sch->schib.scsw.cmd.actl |= SCSW_ACTL_HALT_PEND;
		ret = 0;
		break;
	case 1:		/* Status pending */
	case 2:		/* Busy */
		ret = -EBUSY;
		break;
	case 3:		/* Device not operational */
		ret = -ENODEV;
		break;
	default:
		ret = ccode;
	}
	spin_unlock_irqrestore(sch->lock, flags);
	return ret;
}
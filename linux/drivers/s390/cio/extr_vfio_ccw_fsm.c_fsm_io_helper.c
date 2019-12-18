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
struct TYPE_8__ {int /*<<< orphan*/  lpm; } ;
union orb {TYPE_4__ cmd; } ;
typedef  int /*<<< orphan*/  u32 ;
struct vfio_ccw_private {int /*<<< orphan*/  state; int /*<<< orphan*/  cp; struct subchannel* sch; } ;
struct TYPE_5__ {int /*<<< orphan*/  actl; } ;
struct TYPE_6__ {TYPE_1__ cmd; } ;
struct TYPE_7__ {TYPE_2__ scsw; } ;
struct subchannel {int /*<<< orphan*/  lock; int /*<<< orphan*/  lpm; TYPE_3__ schib; int /*<<< orphan*/  schid; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  ccode ;
typedef  scalar_t__ addr_t ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int EACCES ; 
 int EBUSY ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  SCSW_ACTL_START_PEND ; 
 int /*<<< orphan*/  VFIO_CCW_HEX_EVENT (int,int*,int) ; 
 int /*<<< orphan*/  VFIO_CCW_STATE_CP_PENDING ; 
 int /*<<< orphan*/  VFIO_CCW_TRACE_EVENT (int,char*) ; 
 int /*<<< orphan*/  cio_update_schib (struct subchannel*) ; 
 union orb* cp_get_orb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int ssch (int /*<<< orphan*/ ,union orb*) ; 

__attribute__((used)) static int fsm_io_helper(struct vfio_ccw_private *private)
{
	struct subchannel *sch;
	union orb *orb;
	int ccode;
	__u8 lpm;
	unsigned long flags;
	int ret;

	sch = private->sch;

	spin_lock_irqsave(sch->lock, flags);

	orb = cp_get_orb(&private->cp, (u32)(addr_t)sch, sch->lpm);
	if (!orb) {
		ret = -EIO;
		goto out;
	}

	VFIO_CCW_TRACE_EVENT(5, "stIO");
	VFIO_CCW_TRACE_EVENT(5, dev_name(&sch->dev));

	/* Issue "Start Subchannel" */
	ccode = ssch(sch->schid, orb);

	VFIO_CCW_HEX_EVENT(5, &ccode, sizeof(ccode));

	switch (ccode) {
	case 0:
		/*
		 * Initialize device status information
		 */
		sch->schib.scsw.cmd.actl |= SCSW_ACTL_START_PEND;
		ret = 0;
		private->state = VFIO_CCW_STATE_CP_PENDING;
		break;
	case 1:		/* Status pending */
	case 2:		/* Busy */
		ret = -EBUSY;
		break;
	case 3:		/* Device/path not operational */
	{
		lpm = orb->cmd.lpm;
		if (lpm != 0)
			sch->lpm &= ~lpm;
		else
			sch->lpm = 0;

		if (cio_update_schib(sch))
			ret = -ENODEV;
		else
			ret = sch->lpm ? -EACCES : -ENODEV;
		break;
	}
	default:
		ret = ccode;
	}
out:
	spin_unlock_irqrestore(sch->lock, flags);
	return ret;
}
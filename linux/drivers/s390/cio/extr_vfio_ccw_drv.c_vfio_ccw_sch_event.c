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
struct vfio_ccw_private {scalar_t__ state; scalar_t__ mdev; } ;
struct subchannel {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  todo_work; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  VFIO_CCW_EVENT_NOT_OPER ; 
 scalar_t__ VFIO_CCW_STATE_IDLE ; 
 scalar_t__ VFIO_CCW_STATE_NOT_OPER ; 
 scalar_t__ VFIO_CCW_STATE_STANDBY ; 
 scalar_t__ cio_update_schib (struct subchannel*) ; 
 struct vfio_ccw_private* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  vfio_ccw_fsm_event (struct vfio_ccw_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ work_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vfio_ccw_sch_event(struct subchannel *sch, int process)
{
	struct vfio_ccw_private *private = dev_get_drvdata(&sch->dev);
	unsigned long flags;
	int rc = -EAGAIN;

	spin_lock_irqsave(sch->lock, flags);
	if (!device_is_registered(&sch->dev))
		goto out_unlock;

	if (work_pending(&sch->todo_work))
		goto out_unlock;

	if (cio_update_schib(sch)) {
		vfio_ccw_fsm_event(private, VFIO_CCW_EVENT_NOT_OPER);
		rc = 0;
		goto out_unlock;
	}

	private = dev_get_drvdata(&sch->dev);
	if (private->state == VFIO_CCW_STATE_NOT_OPER) {
		private->state = private->mdev ? VFIO_CCW_STATE_IDLE :
				 VFIO_CCW_STATE_STANDBY;
	}
	rc = 0;

out_unlock:
	spin_unlock_irqrestore(sch->lock, flags);

	return rc;
}
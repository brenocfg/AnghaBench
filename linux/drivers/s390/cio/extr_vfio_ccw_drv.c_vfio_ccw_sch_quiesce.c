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
struct vfio_ccw_private {int /*<<< orphan*/  state; int /*<<< orphan*/ * completion; } ;
struct TYPE_6__ {int /*<<< orphan*/  sch_no; int /*<<< orphan*/  ssid; } ;
struct TYPE_4__ {int /*<<< orphan*/  ena; } ;
struct TYPE_5__ {TYPE_1__ pmcw; } ;
struct subchannel {int /*<<< orphan*/  lock; TYPE_3__ schid; TYPE_2__ schib; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EIO ; 
 int HZ ; 
 int /*<<< orphan*/  VFIO_CCW_STATE_NOT_OPER ; 
 int cio_cancel_halt_clear (struct subchannel*,int*) ; 
 int cio_disable_subchannel (struct subchannel*) ; 
 int /*<<< orphan*/  completion ; 
 struct vfio_ccw_private* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_ccw_work_q ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

int vfio_ccw_sch_quiesce(struct subchannel *sch)
{
	struct vfio_ccw_private *private = dev_get_drvdata(&sch->dev);
	DECLARE_COMPLETION_ONSTACK(completion);
	int iretry, ret = 0;

	spin_lock_irq(sch->lock);
	if (!sch->schib.pmcw.ena)
		goto out_unlock;
	ret = cio_disable_subchannel(sch);
	if (ret != -EBUSY)
		goto out_unlock;

	iretry = 255;
	do {

		ret = cio_cancel_halt_clear(sch, &iretry);

		if (ret == -EIO) {
			pr_err("vfio_ccw: could not quiesce subchannel 0.%x.%04x!\n",
			       sch->schid.ssid, sch->schid.sch_no);
			break;
		}

		/*
		 * Flush all I/O and wait for
		 * cancel/halt/clear completion.
		 */
		private->completion = &completion;
		spin_unlock_irq(sch->lock);

		if (ret == -EBUSY)
			wait_for_completion_timeout(&completion, 3*HZ);

		private->completion = NULL;
		flush_workqueue(vfio_ccw_work_q);
		spin_lock_irq(sch->lock);
		ret = cio_disable_subchannel(sch);
	} while (ret == -EBUSY);
out_unlock:
	private->state = VFIO_CCW_STATE_NOT_OPER;
	spin_unlock_irq(sch->lock);
	return ret;
}
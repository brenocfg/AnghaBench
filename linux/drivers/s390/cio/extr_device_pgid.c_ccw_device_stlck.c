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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct subchannel {int /*<<< orphan*/  lock; } ;
struct stlck_data {int rc; int /*<<< orphan*/  done; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_3__* private; scalar_t__ drv; TYPE_1__ dev; } ;
typedef  scalar_t__ addr_t ;
struct TYPE_5__ {int /*<<< orphan*/  force; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; TYPE_2__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_STATE_BOXED ; 
 int /*<<< orphan*/  DEV_STATE_STEAL_LOCK ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  ccw_device_stlck_start (struct ccw_device*,struct stlck_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccw_request_cancel (struct ccw_device*) ; 
 int /*<<< orphan*/  cio_disable_subchannel (struct subchannel*) ; 
 int cio_enable_subchannel (struct subchannel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

int ccw_device_stlck(struct ccw_device *cdev)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);
	struct stlck_data data;
	u8 *buffer;
	int rc;

	/* Check if steal lock operation is valid for this device. */
	if (cdev->drv) {
		if (!cdev->private->options.force)
			return -EINVAL;
	}
	buffer = kzalloc(64, GFP_DMA | GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;
	init_completion(&data.done);
	data.rc = -EIO;
	spin_lock_irq(sch->lock);
	rc = cio_enable_subchannel(sch, (u32) (addr_t) sch);
	if (rc)
		goto out_unlock;
	/* Perform operation. */
	cdev->private->state = DEV_STATE_STEAL_LOCK;
	ccw_device_stlck_start(cdev, &data, &buffer[0], &buffer[32]);
	spin_unlock_irq(sch->lock);
	/* Wait for operation to finish. */
	if (wait_for_completion_interruptible(&data.done)) {
		/* Got a signal. */
		spin_lock_irq(sch->lock);
		ccw_request_cancel(cdev);
		spin_unlock_irq(sch->lock);
		wait_for_completion(&data.done);
	}
	rc = data.rc;
	/* Check results. */
	spin_lock_irq(sch->lock);
	cio_disable_subchannel(sch);
	cdev->private->state = DEV_STATE_BOXED;
out_unlock:
	spin_unlock_irq(sch->lock);
	kfree(buffer);

	return rc;
}
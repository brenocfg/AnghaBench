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
struct stu300_dev {int cmd_err; int cmd_event; TYPE_1__* pdev; int /*<<< orphan*/  cmd_complete; int /*<<< orphan*/  cmd_issue_lock; } ;
typedef  enum stu300_event { ____Placeholder_stu300_event } stu300_event ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int STU300_ERROR_NONE ; 
 int STU300_EVENT_6 ; 
 int /*<<< orphan*/  STU300_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stu300_init_hw (struct stu300_dev*) ; 
 int /*<<< orphan*/  stu300_irq_enable (struct stu300_dev*) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stu300_await_event(struct stu300_dev *dev,
				enum stu300_event mr_event)
{
	int ret;

	/* Is it already here? */
	spin_lock_irq(&dev->cmd_issue_lock);
	dev->cmd_err = STU300_ERROR_NONE;
	dev->cmd_event = mr_event;

	init_completion(&dev->cmd_complete);

	/* Turn on the I2C interrupt for current operation */
	stu300_irq_enable(dev);

	/* Unlock the command block and wait for the event to occur */
	spin_unlock_irq(&dev->cmd_issue_lock);

	ret = wait_for_completion_interruptible_timeout(&dev->cmd_complete,
							STU300_TIMEOUT);
	if (ret < 0) {
		dev_err(&dev->pdev->dev,
		       "wait_for_completion_interruptible_timeout()"
		       "returned %d waiting for event %04x\n", ret, mr_event);
		return ret;
	}

	if (ret == 0) {
		if (mr_event != STU300_EVENT_6) {
			dev_err(&dev->pdev->dev, "controller "
				"timed out waiting for event %d, reinit "
				"hardware\n", mr_event);
			(void) stu300_init_hw(dev);
		}
		return -ETIMEDOUT;
	}

	if (dev->cmd_err != STU300_ERROR_NONE) {
		if (mr_event != STU300_EVENT_6) {
			dev_err(&dev->pdev->dev, "controller "
				"error (await_event) %d waiting for event %d, "
			       "reinit hardware\n", dev->cmd_err, mr_event);
			(void) stu300_init_hw(dev);
		}
		return -EIO;
	}

	return 0;
}
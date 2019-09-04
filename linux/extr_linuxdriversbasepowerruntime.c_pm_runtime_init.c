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
struct TYPE_2__ {int idle_notification; int disable_depth; int runtime_auto; int request_pending; int deferred_resume; int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  suspend_timer; scalar_t__ timer_expires; int /*<<< orphan*/  work; int /*<<< orphan*/  accounting_timestamp; int /*<<< orphan*/  request; int /*<<< orphan*/  child_count; scalar_t__ runtime_error; int /*<<< orphan*/  usage_count; int /*<<< orphan*/  runtime_status; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPM_REQ_NONE ; 
 int /*<<< orphan*/  RPM_SUSPENDED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  pm_runtime_work ; 
 int /*<<< orphan*/  pm_suspend_ignore_children (struct device*,int) ; 
 int /*<<< orphan*/  pm_suspend_timer_fn ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pm_runtime_init(struct device *dev)
{
	dev->power.runtime_status = RPM_SUSPENDED;
	dev->power.idle_notification = false;

	dev->power.disable_depth = 1;
	atomic_set(&dev->power.usage_count, 0);

	dev->power.runtime_error = 0;

	atomic_set(&dev->power.child_count, 0);
	pm_suspend_ignore_children(dev, false);
	dev->power.runtime_auto = true;

	dev->power.request_pending = false;
	dev->power.request = RPM_REQ_NONE;
	dev->power.deferred_resume = false;
	dev->power.accounting_timestamp = jiffies;
	INIT_WORK(&dev->power.work, pm_runtime_work);

	dev->power.timer_expires = 0;
	timer_setup(&dev->power.suspend_timer, pm_suspend_timer_fn, 0);

	init_waitqueue_head(&dev->power.wait_queue);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rc_dev {TYPE_1__* raw; } ;
struct ir_raw_event {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_5__ {int /*<<< orphan*/  expires; } ;
struct TYPE_4__ {int /*<<< orphan*/  edge_spinlock; TYPE_2__ edge_handle; int /*<<< orphan*/  last_event; } ;

/* Variables and functions */
 int EINVAL ; 
 int ir_raw_event_store (struct rc_dev*,struct ir_raw_event*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  mod_timer (TYPE_2__*,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  timer_pending (TYPE_2__*) ; 

int ir_raw_event_store_with_timeout(struct rc_dev *dev, struct ir_raw_event *ev)
{
	ktime_t		now;
	int		rc = 0;

	if (!dev->raw)
		return -EINVAL;

	now = ktime_get();

	spin_lock(&dev->raw->edge_spinlock);
	rc = ir_raw_event_store(dev, ev);

	dev->raw->last_event = now;

	/* timer could be set to timeout (125ms by default) */
	if (!timer_pending(&dev->raw->edge_handle) ||
	    time_after(dev->raw->edge_handle.expires,
		       jiffies + msecs_to_jiffies(15))) {
		mod_timer(&dev->raw->edge_handle,
			  jiffies + msecs_to_jiffies(15));
	}
	spin_unlock(&dev->raw->edge_spinlock);

	return rc;
}
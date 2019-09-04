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
struct rc_dev {scalar_t__ driver_type; int registered; scalar_t__ allowed_protocols; int /*<<< orphan*/  managed_alloc; int /*<<< orphan*/  minor; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  (* close ) (struct rc_dev*) ;scalar_t__ users; int /*<<< orphan*/  timer_repeat; int /*<<< orphan*/  timer_keyup; } ;

/* Variables and functions */
 scalar_t__ RC_DRIVER_IR_RAW ; 
 scalar_t__ RC_PROTO_BIT_CEC ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_lirc_unregister (struct rc_dev*) ; 
 int /*<<< orphan*/  ir_raw_event_unregister (struct rc_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc_free_device (struct rc_dev*) ; 
 int /*<<< orphan*/  rc_free_rx_device (struct rc_dev*) ; 
 int /*<<< orphan*/  rc_ida ; 
 int /*<<< orphan*/  stub1 (struct rc_dev*) ; 

void rc_unregister_device(struct rc_dev *dev)
{
	if (!dev)
		return;

	if (dev->driver_type == RC_DRIVER_IR_RAW)
		ir_raw_event_unregister(dev);

	del_timer_sync(&dev->timer_keyup);
	del_timer_sync(&dev->timer_repeat);

	rc_free_rx_device(dev);

	mutex_lock(&dev->lock);
	if (dev->users && dev->close)
		dev->close(dev);
	dev->registered = false;
	mutex_unlock(&dev->lock);

	/*
	 * lirc device should be freed with dev->registered = false, so
	 * that userspace polling will get notified.
	 */
	if (dev->allowed_protocols != RC_PROTO_BIT_CEC)
		ir_lirc_unregister(dev);

	device_del(&dev->dev);

	ida_simple_remove(&rc_ida, dev->minor);

	if (!dev->managed_alloc)
		rc_free_device(dev);
}
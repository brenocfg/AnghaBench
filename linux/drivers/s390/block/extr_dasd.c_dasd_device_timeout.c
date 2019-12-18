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
struct timer_list {int dummy; } ;
struct dasd_device {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_STOPPED_PENDING ; 
 int /*<<< orphan*/  dasd_device_remove_stop_bits (struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_schedule_device_bh (struct dasd_device*) ; 
 struct dasd_device* from_timer (struct dasd_device*,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void dasd_device_timeout(struct timer_list *t)
{
	unsigned long flags;
	struct dasd_device *device;

	device = from_timer(device, t, timer);
	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	/* re-activate request queue */
	dasd_device_remove_stop_bits(device, DASD_STOPPED_PENDING);
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
	dasd_schedule_device_bh(device);
}
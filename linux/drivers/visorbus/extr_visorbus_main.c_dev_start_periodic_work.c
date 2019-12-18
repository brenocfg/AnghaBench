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
struct TYPE_2__ {scalar_t__ expires; } ;
struct visor_device {int timer_active; TYPE_1__ timer; int /*<<< orphan*/  device; scalar_t__ being_removed; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ POLLJIFFIES_NORMALCHANNEL ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static int dev_start_periodic_work(struct visor_device *dev)
{
	if (dev->being_removed || dev->timer_active)
		return -EINVAL;

	/* now up by at least 2 */
	get_device(&dev->device);
	dev->timer.expires = jiffies + POLLJIFFIES_NORMALCHANNEL;
	add_timer(&dev->timer);
	dev->timer_active = true;
	return 0;
}
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
struct visor_driver {int /*<<< orphan*/  (* channel_interrupt ) (struct visor_device*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct visor_device {int /*<<< orphan*/  timer; TYPE_1__ device; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 scalar_t__ POLLJIFFIES_NORMALCHANNEL ; 
 struct visor_device* dev ; 
 struct visor_device* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct visor_device*) ; 
 int /*<<< orphan*/  timer ; 
 struct visor_driver* to_visor_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dev_periodic_work(struct timer_list *t)
{
	struct visor_device *dev = from_timer(dev, t, timer);
	struct visor_driver *drv = to_visor_driver(dev->device.driver);

	drv->channel_interrupt(dev);
	mod_timer(&dev->timer, jiffies + POLLJIFFIES_NORMALCHANNEL);
}
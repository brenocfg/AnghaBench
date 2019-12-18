#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ expires; } ;
struct ksz_device {scalar_t__ reset_gpio; int /*<<< orphan*/  ds; TYPE_1__* dev_ops; int /*<<< orphan*/  mib_read; TYPE_2__ mib_read_timer; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* exit ) (struct ksz_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  dsa_unregister_switch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (struct ksz_device*) ; 

void ksz_switch_remove(struct ksz_device *dev)
{
	/* timer started */
	if (dev->mib_read_timer.expires) {
		del_timer_sync(&dev->mib_read_timer);
		flush_work(&dev->mib_read);
	}

	dev->dev_ops->exit(dev);
	dsa_unregister_switch(dev->ds);

	if (dev->reset_gpio)
		gpiod_set_value_cansleep(dev->reset_gpio, 1);

}
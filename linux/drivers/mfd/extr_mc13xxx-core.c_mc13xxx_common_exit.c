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
struct mc13xxx {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq_data; int /*<<< orphan*/  irq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct mc13xxx* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mfd_remove_devices (struct device*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mc13xxx_common_exit(struct device *dev)
{
	struct mc13xxx *mc13xxx = dev_get_drvdata(dev);

	mfd_remove_devices(dev);
	regmap_del_irq_chip(mc13xxx->irq, mc13xxx->irq_data);
	mutex_destroy(&mc13xxx->lock);

	return 0;
}
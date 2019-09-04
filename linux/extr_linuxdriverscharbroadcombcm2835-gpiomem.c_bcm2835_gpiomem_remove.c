#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm2835_gpiomem_cdev ; 
 int /*<<< orphan*/  bcm2835_gpiomem_class ; 
 int /*<<< orphan*/  bcm2835_gpiomem_devid ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* inst ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm2835_gpiomem_remove(struct platform_device *pdev)
{
	struct device *dev = inst->dev;

	kfree(inst);
	device_destroy(bcm2835_gpiomem_class, bcm2835_gpiomem_devid);
	class_destroy(bcm2835_gpiomem_class);
	cdev_del(&bcm2835_gpiomem_cdev);
	unregister_chrdev_region(bcm2835_gpiomem_devid, 1);

	dev_info(dev, "GPIO mem driver removed - OK");
	return 0;
}
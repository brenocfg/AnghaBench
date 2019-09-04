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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm2835_smi_cdev ; 
 int /*<<< orphan*/  bcm2835_smi_class ; 
 int /*<<< orphan*/  bcm2835_smi_devid ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* inst ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm2835_smi_dev_remove(struct platform_device *pdev)
{
	device_destroy(bcm2835_smi_class, bcm2835_smi_devid);
	class_destroy(bcm2835_smi_class);
	cdev_del(&bcm2835_smi_cdev);
	unregister_chrdev_region(bcm2835_smi_devid, 1);

	dev_info(inst->dev, "SMI character dev removed - OK");
	return 0;
}
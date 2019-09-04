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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct bcm_device {int /*<<< orphan*/  list; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int bcm_acpi_probe (struct bcm_device*) ; 
 int /*<<< orphan*/  bcm_device_list ; 
 int /*<<< orphan*/  bcm_device_lock ; 
 int bcm_get_resources (struct bcm_device*) ; 
 int bcm_gpio_set_power (struct bcm_device*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct bcm_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ has_acpi_companion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bcm_device*) ; 

__attribute__((used)) static int bcm_probe(struct platform_device *pdev)
{
	struct bcm_device *dev;
	int ret;

	dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	dev->dev = &pdev->dev;
	dev->irq = platform_get_irq(pdev, 0);

	if (has_acpi_companion(&pdev->dev)) {
		ret = bcm_acpi_probe(dev);
		if (ret)
			return ret;
	}

	ret = bcm_get_resources(dev);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, dev);

	dev_info(&pdev->dev, "%s device registered.\n", dev->name);

	/* Place this instance on the device list */
	mutex_lock(&bcm_device_lock);
	list_add_tail(&dev->list, &bcm_device_list);
	mutex_unlock(&bcm_device_lock);

	ret = bcm_gpio_set_power(dev, false);
	if (ret)
		dev_err(&pdev->dev, "Failed to power down\n");

	return 0;
}
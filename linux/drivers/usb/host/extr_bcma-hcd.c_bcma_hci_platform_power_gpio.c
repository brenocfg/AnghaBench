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
struct bcma_hcd_device {int /*<<< orphan*/  gpio_desc; } ;
struct bcma_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 struct bcma_hcd_device* bcma_get_drvdata (struct bcma_device*) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bcma_hci_platform_power_gpio(struct bcma_device *dev, bool val)
{
	struct bcma_hcd_device *usb_dev = bcma_get_drvdata(dev);

	if (IS_ERR_OR_NULL(usb_dev->gpio_desc))
		return;

	gpiod_set_value(usb_dev->gpio_desc, val);
}
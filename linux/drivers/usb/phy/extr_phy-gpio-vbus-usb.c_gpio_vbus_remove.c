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
struct gpio_vbus_data {int /*<<< orphan*/  phy; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct gpio_vbus_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  usb_remove_phy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gpio_vbus_remove(struct platform_device *pdev)
{
	struct gpio_vbus_data *gpio_vbus = platform_get_drvdata(pdev);

	device_init_wakeup(&pdev->dev, 0);
	cancel_delayed_work_sync(&gpio_vbus->work);

	usb_remove_phy(&gpio_vbus->phy);

	return 0;
}
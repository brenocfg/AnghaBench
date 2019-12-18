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
struct sun4i_usb_phy_data {scalar_t__ id_det_irq; scalar_t__ vbus_det_irq; int /*<<< orphan*/  detect; int /*<<< orphan*/  vbus_power_nb; scalar_t__ vbus_power_nb_registered; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct sun4i_usb_phy_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  devm_free_irq (struct device*,scalar_t__,struct sun4i_usb_phy_data*) ; 
 int /*<<< orphan*/  power_supply_unreg_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sun4i_usb_phy_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct sun4i_usb_phy_data *data = dev_get_drvdata(dev);

	if (data->vbus_power_nb_registered)
		power_supply_unreg_notifier(&data->vbus_power_nb);
	if (data->id_det_irq > 0)
		devm_free_irq(dev, data->id_det_irq, data);
	if (data->vbus_det_irq > 0)
		devm_free_irq(dev, data->vbus_det_irq, data);

	cancel_delayed_work_sync(&data->detect);

	return 0;
}
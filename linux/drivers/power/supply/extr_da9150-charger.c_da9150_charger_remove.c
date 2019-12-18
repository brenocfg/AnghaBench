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
struct platform_device {int dummy; } ;
struct da9150_charger {int /*<<< orphan*/  vbat_chan; int /*<<< orphan*/  tjunc_chan; int /*<<< orphan*/  vbus_chan; int /*<<< orphan*/  ibus_chan; int /*<<< orphan*/  usb; int /*<<< orphan*/  battery; int /*<<< orphan*/  otg_nb; int /*<<< orphan*/  usb_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int,struct da9150_charger*) ; 
 int /*<<< orphan*/  iio_channel_release (int /*<<< orphan*/ ) ; 
 struct da9150_charger* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int da9150_charger_remove(struct platform_device *pdev)
{
	struct da9150_charger *charger = platform_get_drvdata(pdev);
	int irq;

	/* Make sure IRQs are released before unregistering power supplies */
	irq = platform_get_irq_byname(pdev, "CHG_VBUS");
	free_irq(irq, charger);

	irq = platform_get_irq_byname(pdev, "CHG_VFAULT");
	free_irq(irq, charger);

	irq = platform_get_irq_byname(pdev, "CHG_TJUNC");
	free_irq(irq, charger);

	irq = platform_get_irq_byname(pdev, "CHG_STATUS");
	free_irq(irq, charger);

	if (!IS_ERR_OR_NULL(charger->usb_phy))
		usb_unregister_notifier(charger->usb_phy, &charger->otg_nb);

	power_supply_unregister(charger->battery);
	power_supply_unregister(charger->usb);

	/* Release ADC channels */
	iio_channel_release(charger->ibus_chan);
	iio_channel_release(charger->vbus_chan);
	iio_channel_release(charger->tjunc_chan);
	iio_channel_release(charger->vbat_chan);

	return 0;
}
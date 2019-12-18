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
struct wm8350_power {int /*<<< orphan*/  usb; int /*<<< orphan*/  ac; int /*<<< orphan*/  battery; } ;
struct wm8350 {struct wm8350_power power; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_charger_state ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_charger_irq (struct wm8350*) ; 
 struct wm8350* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8350_power_remove(struct platform_device *pdev)
{
	struct wm8350 *wm8350 = platform_get_drvdata(pdev);
	struct wm8350_power *power = &wm8350->power;

	free_charger_irq(wm8350);
	device_remove_file(&pdev->dev, &dev_attr_charger_state);
	power_supply_unregister(power->battery);
	power_supply_unregister(power->ac);
	power_supply_unregister(power->usb);
	return 0;
}
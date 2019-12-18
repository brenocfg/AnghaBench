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
struct wm831x_power {int /*<<< orphan*/  usb; int /*<<< orphan*/  wall; int /*<<< orphan*/  battery; scalar_t__ have_battery; int /*<<< orphan*/  usb_notify; scalar_t__ usb_phy; struct wm831x* wm831x; } ;
struct wm831x {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  free_irq (int,struct wm831x_power*) ; 
 struct wm831x_power* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_get_irq_byname (struct platform_device*,char*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unregister_notifier (scalar_t__,int /*<<< orphan*/ *) ; 
 char** wm831x_bat_irqs ; 
 int wm831x_irq (struct wm831x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm831x_power_remove(struct platform_device *pdev)
{
	struct wm831x_power *wm831x_power = platform_get_drvdata(pdev);
	struct wm831x *wm831x = wm831x_power->wm831x;
	int irq, i;

	if (wm831x_power->usb_phy) {
		usb_unregister_notifier(wm831x_power->usb_phy,
					&wm831x_power->usb_notify);
	}

	for (i = 0; i < ARRAY_SIZE(wm831x_bat_irqs); i++) {
		irq = wm831x_irq(wm831x, 
				 platform_get_irq_byname(pdev,
							 wm831x_bat_irqs[i]));
		free_irq(irq, wm831x_power);
	}

	irq = wm831x_irq(wm831x, platform_get_irq_byname(pdev, "PWR SRC"));
	free_irq(irq, wm831x_power);

	irq = wm831x_irq(wm831x, platform_get_irq_byname(pdev, "SYSLO"));
	free_irq(irq, wm831x_power);

	if (wm831x_power->have_battery)
		power_supply_unregister(wm831x_power->battery);
	power_supply_unregister(wm831x_power->wall);
	power_supply_unregister(wm831x_power->usb);
	return 0;
}
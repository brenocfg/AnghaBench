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
struct wm831x_power {int /*<<< orphan*/  battery; scalar_t__ have_battery; struct wm831x* wm831x; } ;
struct wm831x {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t wm831x_bat_irq(int irq, void *data)
{
	struct wm831x_power *wm831x_power = data;
	struct wm831x *wm831x = wm831x_power->wm831x;

	dev_dbg(wm831x->dev, "Battery status changed: %d\n", irq);

	/* The battery charger is autonomous so we don't need to do
	 * anything except kick user space */
	if (wm831x_power->have_battery)
		power_supply_changed(wm831x_power->battery);

	return IRQ_HANDLED;
}
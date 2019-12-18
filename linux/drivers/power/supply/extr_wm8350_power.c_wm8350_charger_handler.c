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
struct wm8350_power {int /*<<< orphan*/  ac; int /*<<< orphan*/  usb; int /*<<< orphan*/  battery; struct wm8350_charger_policy* policy; } ;
struct wm8350_charger_policy {int dummy; } ;
struct wm8350 {int irq_base; int /*<<< orphan*/  dev; struct wm8350_power power; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  WM8350_BATTERY_CHARGER_CONTROL_1 ; 
 int /*<<< orphan*/  WM8350_CHG_FAST ; 
#define  WM8350_IRQ_CHG_BAT_COLD 140 
#define  WM8350_IRQ_CHG_BAT_FAIL 139 
#define  WM8350_IRQ_CHG_BAT_HOT 138 
#define  WM8350_IRQ_CHG_END 137 
#define  WM8350_IRQ_CHG_FAST_RDY 136 
#define  WM8350_IRQ_CHG_START 135 
#define  WM8350_IRQ_CHG_TO 134 
#define  WM8350_IRQ_CHG_VBATT_LT_2P85 133 
#define  WM8350_IRQ_CHG_VBATT_LT_3P1 132 
#define  WM8350_IRQ_CHG_VBATT_LT_3P9 131 
#define  WM8350_IRQ_EXT_BAT_FB 130 
#define  WM8350_IRQ_EXT_USB_FB 129 
#define  WM8350_IRQ_EXT_WALL_FB 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_charger_config (struct wm8350*,struct wm8350_charger_policy*) ; 
 int /*<<< orphan*/  wm8350_reg_lock (struct wm8350*) ; 
 int /*<<< orphan*/  wm8350_reg_unlock (struct wm8350*) ; 
 int /*<<< orphan*/  wm8350_set_bits (struct wm8350*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t wm8350_charger_handler(int irq, void *data)
{
	struct wm8350 *wm8350 = data;
	struct wm8350_power *power = &wm8350->power;
	struct wm8350_charger_policy *policy = power->policy;

	switch (irq - wm8350->irq_base) {
	case WM8350_IRQ_CHG_BAT_FAIL:
		dev_err(wm8350->dev, "battery failed\n");
		break;
	case WM8350_IRQ_CHG_TO:
		dev_err(wm8350->dev, "charger timeout\n");
		power_supply_changed(power->battery);
		break;

	case WM8350_IRQ_CHG_BAT_HOT:
	case WM8350_IRQ_CHG_BAT_COLD:
	case WM8350_IRQ_CHG_START:
	case WM8350_IRQ_CHG_END:
		power_supply_changed(power->battery);
		break;

	case WM8350_IRQ_CHG_FAST_RDY:
		dev_dbg(wm8350->dev, "fast charger ready\n");
		wm8350_charger_config(wm8350, policy);
		wm8350_reg_unlock(wm8350);
		wm8350_set_bits(wm8350, WM8350_BATTERY_CHARGER_CONTROL_1,
				WM8350_CHG_FAST);
		wm8350_reg_lock(wm8350);
		break;

	case WM8350_IRQ_CHG_VBATT_LT_3P9:
		dev_warn(wm8350->dev, "battery < 3.9V\n");
		break;
	case WM8350_IRQ_CHG_VBATT_LT_3P1:
		dev_warn(wm8350->dev, "battery < 3.1V\n");
		break;
	case WM8350_IRQ_CHG_VBATT_LT_2P85:
		dev_warn(wm8350->dev, "battery < 2.85V\n");
		break;

		/* Supply change.  We will overnotify but it should do
		 * no harm. */
	case WM8350_IRQ_EXT_USB_FB:
	case WM8350_IRQ_EXT_WALL_FB:
		wm8350_charger_config(wm8350, policy);
		/* Fall through */
	case WM8350_IRQ_EXT_BAT_FB:
		power_supply_changed(power->battery);
		power_supply_changed(power->usb);
		power_supply_changed(power->ac);
		break;

	default:
		dev_err(wm8350->dev, "Unknown interrupt %d\n", irq);
	}

	return IRQ_HANDLED;
}
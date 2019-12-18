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
struct wm8350 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8350_IRQ_CHG_BAT_COLD ; 
 int /*<<< orphan*/  WM8350_IRQ_CHG_BAT_FAIL ; 
 int /*<<< orphan*/  WM8350_IRQ_CHG_BAT_HOT ; 
 int /*<<< orphan*/  WM8350_IRQ_CHG_END ; 
 int /*<<< orphan*/  WM8350_IRQ_CHG_FAST_RDY ; 
 int /*<<< orphan*/  WM8350_IRQ_CHG_START ; 
 int /*<<< orphan*/  WM8350_IRQ_CHG_TO ; 
 int /*<<< orphan*/  WM8350_IRQ_CHG_VBATT_LT_2P85 ; 
 int /*<<< orphan*/  WM8350_IRQ_CHG_VBATT_LT_3P1 ; 
 int /*<<< orphan*/  WM8350_IRQ_CHG_VBATT_LT_3P9 ; 
 int /*<<< orphan*/  WM8350_IRQ_EXT_BAT_FB ; 
 int /*<<< orphan*/  WM8350_IRQ_EXT_USB_FB ; 
 int /*<<< orphan*/  WM8350_IRQ_EXT_WALL_FB ; 
 int /*<<< orphan*/  wm8350_charger_handler ; 
 int /*<<< orphan*/  wm8350_register_irq (struct wm8350*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct wm8350*) ; 

__attribute__((used)) static void wm8350_init_charger(struct wm8350 *wm8350)
{
	/* register our interest in charger events */
	wm8350_register_irq(wm8350, WM8350_IRQ_CHG_BAT_HOT,
			    wm8350_charger_handler, 0, "Battery hot", wm8350);
	wm8350_register_irq(wm8350, WM8350_IRQ_CHG_BAT_COLD,
			    wm8350_charger_handler, 0, "Battery cold", wm8350);
	wm8350_register_irq(wm8350, WM8350_IRQ_CHG_BAT_FAIL,
			    wm8350_charger_handler, 0, "Battery fail", wm8350);
	wm8350_register_irq(wm8350, WM8350_IRQ_CHG_TO,
			    wm8350_charger_handler, 0,
			    "Charger timeout", wm8350);
	wm8350_register_irq(wm8350, WM8350_IRQ_CHG_END,
			    wm8350_charger_handler, 0,
			    "Charge end", wm8350);
	wm8350_register_irq(wm8350, WM8350_IRQ_CHG_START,
			    wm8350_charger_handler, 0,
			    "Charge start", wm8350);
	wm8350_register_irq(wm8350, WM8350_IRQ_CHG_FAST_RDY,
			    wm8350_charger_handler, 0,
			    "Fast charge ready", wm8350);
	wm8350_register_irq(wm8350, WM8350_IRQ_CHG_VBATT_LT_3P9,
			    wm8350_charger_handler, 0,
			    "Battery <3.9V", wm8350);
	wm8350_register_irq(wm8350, WM8350_IRQ_CHG_VBATT_LT_3P1,
			    wm8350_charger_handler, 0,
			    "Battery <3.1V", wm8350);
	wm8350_register_irq(wm8350, WM8350_IRQ_CHG_VBATT_LT_2P85,
			    wm8350_charger_handler, 0,
			    "Battery <2.85V", wm8350);

	/* and supply change events */
	wm8350_register_irq(wm8350, WM8350_IRQ_EXT_USB_FB,
			    wm8350_charger_handler, 0, "USB", wm8350);
	wm8350_register_irq(wm8350, WM8350_IRQ_EXT_WALL_FB,
			    wm8350_charger_handler, 0, "Wall", wm8350);
	wm8350_register_irq(wm8350, WM8350_IRQ_EXT_BAT_FB,
			    wm8350_charger_handler, 0, "Battery", wm8350);
}
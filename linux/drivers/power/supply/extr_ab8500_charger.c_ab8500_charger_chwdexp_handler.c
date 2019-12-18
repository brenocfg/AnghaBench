#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  psy; } ;
struct TYPE_8__ {int wd_expired; scalar_t__ charger_online; } ;
struct TYPE_7__ {int /*<<< orphan*/  psy; } ;
struct TYPE_6__ {int wd_expired; scalar_t__ charger_online; } ;
struct ab8500_charger {TYPE_1__ usb_chg; TYPE_4__ usb; TYPE_3__ ac_chg; TYPE_2__ ac; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ab8500_power_supply_changed (struct ab8500_charger*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static irqreturn_t ab8500_charger_chwdexp_handler(int irq, void *_di)
{
	struct ab8500_charger *di = _di;

	dev_dbg(di->dev, "Charger watchdog expired\n");

	/*
	 * The charger that was online when the watchdog expired
	 * needs to be restarted for charging to start again
	 */
	if (di->ac.charger_online) {
		di->ac.wd_expired = true;
		ab8500_power_supply_changed(di, di->ac_chg.psy);
	}
	if (di->usb.charger_online) {
		di->usb.wd_expired = true;
		ab8500_power_supply_changed(di, di->usb_chg.psy);
	}

	return IRQ_HANDLED;
}
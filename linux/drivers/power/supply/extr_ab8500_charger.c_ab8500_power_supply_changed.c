#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct power_supply {int dummy; } ;
struct TYPE_3__ {scalar_t__ charger_connected; } ;
struct TYPE_4__ {scalar_t__ charger_connected; } ;
struct ab8500_charger {int autopower; TYPE_1__ usb; TYPE_2__ ac; scalar_t__ autopower_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ab8500_enable_disable_sw_fallback (struct ab8500_charger*,int) ; 
 int /*<<< orphan*/  power_supply_changed (struct power_supply*) ; 

__attribute__((used)) static void ab8500_power_supply_changed(struct ab8500_charger *di,
					struct power_supply *psy)
{
	if (di->autopower_cfg) {
		if (!di->usb.charger_connected &&
		    !di->ac.charger_connected &&
		    di->autopower) {
			di->autopower = false;
			ab8500_enable_disable_sw_fallback(di, false);
		} else if (!di->autopower &&
			   (di->ac.charger_connected ||
			    di->usb.charger_connected)) {
			di->autopower = true;
			ab8500_enable_disable_sw_fallback(di, true);
		}
	}
	power_supply_changed(psy);
}
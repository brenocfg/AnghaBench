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
typedef  int u16 ;
struct wm8350 {int dummy; } ;

/* Variables and functions */
 int POWER_SUPPLY_HEALTH_COLD ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_OVERHEAT ; 
 int POWER_SUPPLY_HEALTH_UNSPEC_FAILURE ; 
 int /*<<< orphan*/  WM8350_CHARGER_OVERRIDES ; 
 int WM8350_CHG_BATT_COLD_OVRDE ; 
 int WM8350_CHG_BATT_HOT_OVRDE ; 
 int wm8350_read_battery_uvolts (struct wm8350*) ; 
 int wm8350_reg_read (struct wm8350*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8350_bat_check_health(struct wm8350 *wm8350)
{
	u16 reg;

	if (wm8350_read_battery_uvolts(wm8350) < 2850000)
		return POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;

	reg = wm8350_reg_read(wm8350, WM8350_CHARGER_OVERRIDES);
	if (reg & WM8350_CHG_BATT_HOT_OVRDE)
		return POWER_SUPPLY_HEALTH_OVERHEAT;

	if (reg & WM8350_CHG_BATT_COLD_OVRDE)
		return POWER_SUPPLY_HEALTH_COLD;

	return POWER_SUPPLY_HEALTH_GOOD;
}
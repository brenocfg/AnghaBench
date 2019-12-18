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
struct pm2xxx_charger {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PM2XXX_INT2_ITVPWR1PLUG ; 
 int PM2XXX_INT2_ITVPWR1UNPLUG ; 
 int PM2XXX_INT2_ITVPWR2PLUG ; 
 int PM2XXX_INT2_ITVPWR2UNPLUG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int pm2xxx_charger_itv_pwr_plug_mngt (struct pm2xxx_charger*,int) ; 
 int pm2xxx_charger_itv_pwr_unplug_mngt (struct pm2xxx_charger*,int) ; 

__attribute__((used)) static int pm2_int_reg1(void *pm2_data, int val)
{
	struct pm2xxx_charger *pm2 = pm2_data;
	int ret = 0;

	if (val & (PM2XXX_INT2_ITVPWR1PLUG | PM2XXX_INT2_ITVPWR2PLUG)) {
		dev_dbg(pm2->dev , "Main charger plugged\n");
		ret = pm2xxx_charger_itv_pwr_plug_mngt(pm2, val &
			(PM2XXX_INT2_ITVPWR1PLUG | PM2XXX_INT2_ITVPWR2PLUG));
	}

	if (val &
		(PM2XXX_INT2_ITVPWR1UNPLUG | PM2XXX_INT2_ITVPWR2UNPLUG)) {
		dev_dbg(pm2->dev , "Main charger unplugged\n");
		ret = pm2xxx_charger_itv_pwr_unplug_mngt(pm2, val &
						(PM2XXX_INT2_ITVPWR1UNPLUG |
						PM2XXX_INT2_ITVPWR2UNPLUG));
	}

	return ret;
}
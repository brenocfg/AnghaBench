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
struct pm2xxx_charger {int /*<<< orphan*/  dev; int /*<<< orphan*/  failure_case; } ;

/* Variables and functions */
 int PM2XXX_INT4_ITBATTFULL ; 
 int PM2XXX_INT4_ITCHARGINGON ; 
 int PM2XXX_INT4_ITCVPHASE ; 
 int PM2XXX_INT4_ITVPWR1OVV ; 
 int PM2XXX_INT4_ITVPWR2OVV ; 
 int PM2XXX_INT4_ITVRESUME ; 
 int PM2XXX_INT4_S_ITBATTEMPCOLD ; 
 int PM2XXX_INT4_S_ITBATTEMPHOT ; 
 int /*<<< orphan*/  VPWR_OVV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int pm2xxx_charger_batt_therm_mngt (struct pm2xxx_charger*,int) ; 
 int pm2xxx_charger_ovv_mngt (struct pm2xxx_charger*,int) ; 

__attribute__((used)) static int pm2_int_reg3(void *pm2_data, int val)
{
	struct pm2xxx_charger *pm2 = pm2_data;
	int ret = 0;

	if (val & (PM2XXX_INT4_ITCHARGINGON)) {
		dev_dbg(pm2->dev ,
			"chargind operation has started\n");
	}

	if (val & (PM2XXX_INT4_ITVRESUME)) {
		dev_dbg(pm2->dev,
			"battery discharged down to VResume threshold\n");
	}

	if (val & (PM2XXX_INT4_ITBATTFULL)) {
		dev_dbg(pm2->dev , "battery fully detected\n");
	}

	if (val & (PM2XXX_INT4_ITCVPHASE)) {
		dev_dbg(pm2->dev, "CV phase enter with 0.5C charging\n");
	}

	if (val & (PM2XXX_INT4_ITVPWR2OVV | PM2XXX_INT4_ITVPWR1OVV)) {
		pm2->failure_case = VPWR_OVV;
		ret = pm2xxx_charger_ovv_mngt(pm2, val &
			(PM2XXX_INT4_ITVPWR2OVV | PM2XXX_INT4_ITVPWR1OVV));
		dev_dbg(pm2->dev, "VPWR/VSYSTEM overvoltage detected\n");
	}

	if (val & (PM2XXX_INT4_S_ITBATTEMPCOLD |
				PM2XXX_INT4_S_ITBATTEMPHOT)) {
		ret = pm2xxx_charger_batt_therm_mngt(pm2, val &
			(PM2XXX_INT4_S_ITBATTEMPCOLD |
			PM2XXX_INT4_S_ITBATTEMPHOT));
		dev_dbg(pm2->dev, "BTEMP is too Low/High\n");
	}

	return ret;
}
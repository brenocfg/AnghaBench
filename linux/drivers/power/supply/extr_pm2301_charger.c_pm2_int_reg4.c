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
 int PM2XXX_INT5_ITTHERMALSHUTDOWNFALL ; 
 int PM2XXX_INT5_ITTHERMALSHUTDOWNRISE ; 
 int PM2XXX_INT5_ITTHERMALWARNINGFALL ; 
 int PM2XXX_INT5_ITTHERMALWARNINGRISE ; 
 int PM2XXX_INT5_ITVSYSTEMOVV ; 
 int /*<<< orphan*/  VSYSTEM_OVV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int pm2xxx_charger_die_therm_mngt (struct pm2xxx_charger*,int) ; 
 int pm2xxx_charger_ovv_mngt (struct pm2xxx_charger*,int) ; 

__attribute__((used)) static int pm2_int_reg4(void *pm2_data, int val)
{
	struct pm2xxx_charger *pm2 = pm2_data;
	int ret = 0;

	if (val & PM2XXX_INT5_ITVSYSTEMOVV) {
		pm2->failure_case = VSYSTEM_OVV;
		ret = pm2xxx_charger_ovv_mngt(pm2, val &
						PM2XXX_INT5_ITVSYSTEMOVV);
		dev_dbg(pm2->dev, "VSYSTEM overvoltage detected\n");
	}

	if (val & (PM2XXX_INT5_ITTHERMALWARNINGFALL |
				PM2XXX_INT5_ITTHERMALWARNINGRISE |
				PM2XXX_INT5_ITTHERMALSHUTDOWNFALL |
				PM2XXX_INT5_ITTHERMALSHUTDOWNRISE)) {
		dev_dbg(pm2->dev, "BTEMP die temperature is too Low/High\n");
		ret = pm2xxx_charger_die_therm_mngt(pm2, val &
			(PM2XXX_INT5_ITTHERMALWARNINGFALL |
			PM2XXX_INT5_ITTHERMALWARNINGRISE |
			PM2XXX_INT5_ITTHERMALSHUTDOWNFALL |
			PM2XXX_INT5_ITTHERMALSHUTDOWNRISE));
	}

	return ret;
}
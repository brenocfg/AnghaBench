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
struct bd70528_psy {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int BD70528_MASK_CHG_STAT ; 
 int /*<<< orphan*/  BD70528_REG_CHG_CURR_STAT ; 
#define  CHG_STAT_BAT_ERR 139 
#define  CHG_STAT_DONE 138 
#define  CHG_STAT_FAST 137 
#define  CHG_STAT_OTP_DONE 136 
#define  CHG_STAT_OTP_FAST 135 
#define  CHG_STAT_OTP_TRICKLE 134 
#define  CHG_STAT_SUSPEND 133 
#define  CHG_STAT_TOPOFF 132 
#define  CHG_STAT_TRICKLE 131 
#define  CHG_STAT_TSD_FAST 130 
#define  CHG_STAT_TSD_TOPOFF 129 
#define  CHG_STAT_TSD_TRICKLE 128 
 int POWER_SUPPLY_CHARGE_TYPE_FAST ; 
 int POWER_SUPPLY_CHARGE_TYPE_NONE ; 
 int POWER_SUPPLY_CHARGE_TYPE_TRICKLE ; 
 int POWER_SUPPLY_CHARGE_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int bd70528_get_charge_type(struct bd70528_psy *bdpsy, int *val)
{
	int ret;
	unsigned int v;

	ret = regmap_read(bdpsy->regmap, BD70528_REG_CHG_CURR_STAT, &v);
	if (ret) {
		dev_err(bdpsy->dev, "Charger state read failure %d\n",
			ret);
		return ret;
	}

	switch (v & BD70528_MASK_CHG_STAT) {
	case CHG_STAT_TRICKLE:
		*val = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
		break;
	case CHG_STAT_FAST:
	case CHG_STAT_TOPOFF:
		*val = POWER_SUPPLY_CHARGE_TYPE_FAST;
		break;
	case CHG_STAT_DONE:
	case CHG_STAT_SUSPEND:
	/* Maybe we should check the CHG_TTRI_EN? */
	case CHG_STAT_OTP_TRICKLE:
	case CHG_STAT_OTP_FAST:
	case CHG_STAT_OTP_DONE:
	case CHG_STAT_TSD_TRICKLE:
	case CHG_STAT_TSD_FAST:
	case CHG_STAT_TSD_TOPOFF:
	case CHG_STAT_BAT_ERR:
		*val = POWER_SUPPLY_CHARGE_TYPE_NONE;
		break;
	default:
		*val = POWER_SUPPLY_CHARGE_TYPE_UNKNOWN;
		break;
	}

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smb347_charger {int /*<<< orphan*/  regmap; TYPE_1__* pdata; } ;
struct TYPE_2__ {int pre_to_fast_voltage; int max_charge_voltage; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_FLOAT_VOLTAGE ; 
 int /*<<< orphan*/  CFG_FLOAT_VOLTAGE_FLOAT_MASK ; 
 int /*<<< orphan*/  CFG_FLOAT_VOLTAGE_THRESHOLD_MASK ; 
 int CFG_FLOAT_VOLTAGE_THRESHOLD_SHIFT ; 
 int clamp_val (int,int,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smb347_set_voltage_limits(struct smb347_charger *smb)
{
	int ret;

	if (smb->pdata->pre_to_fast_voltage) {
		ret = smb->pdata->pre_to_fast_voltage;

		/* uV */
		ret = clamp_val(ret, 2400000, 3000000) - 2400000;
		ret /= 200000;

		ret = regmap_update_bits(smb->regmap, CFG_FLOAT_VOLTAGE,
				CFG_FLOAT_VOLTAGE_THRESHOLD_MASK,
				ret << CFG_FLOAT_VOLTAGE_THRESHOLD_SHIFT);
		if (ret < 0)
			return ret;
	}

	if (smb->pdata->max_charge_voltage) {
		ret = smb->pdata->max_charge_voltage;

		/* uV */
		ret = clamp_val(ret, 3500000, 4500000) - 3500000;
		ret /= 20000;

		ret = regmap_update_bits(smb->regmap, CFG_FLOAT_VOLTAGE,
					 CFG_FLOAT_VOLTAGE_FLOAT_MASK, ret);
		if (ret < 0)
			return ret;
	}

	return 0;
}
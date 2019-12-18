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
struct max77693_charger {TYPE_1__* max77693; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHG_CNFG_12_VCHGINREG_MASK ; 
 unsigned int CHG_CNFG_12_VCHGINREG_SHIFT ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAX77693_CHG_REG_CHG_CNFG_12 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int max77693_set_charge_input_threshold_volt(struct max77693_charger *chg,
		unsigned int uvolt)
{
	unsigned int data;

	switch (uvolt) {
	case 4300000:
		data = 0x0;
		break;
	case 4700000:
	case 4800000:
	case 4900000:
		data = (uvolt - 4700000) / 100000;
		break;
	default:
		dev_err(chg->dev, "Wrong value for charge input voltage regulation threshold\n");
		return -EINVAL;
	}

	data <<= CHG_CNFG_12_VCHGINREG_SHIFT;

	dev_dbg(chg->dev, "Charge input voltage regulation threshold: %u (0x%x)\n",
			uvolt, data);

	return regmap_update_bits(chg->max77693->regmap,
			MAX77693_CHG_REG_CHG_CNFG_12,
			CHG_CNFG_12_VCHGINREG_MASK, data);
}
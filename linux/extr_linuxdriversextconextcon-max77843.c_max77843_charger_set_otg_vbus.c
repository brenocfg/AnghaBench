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
struct max77843_muic_info {struct max77693_dev* max77843; } ;
struct max77693_dev {int /*<<< orphan*/  regmap_chg; } ;

/* Variables and functions */
 unsigned int MAX77843_CHG_BOOST_MASK ; 
 unsigned int MAX77843_CHG_BUCK_MASK ; 
 unsigned int MAX77843_CHG_ENABLE ; 
 int /*<<< orphan*/  MAX77843_CHG_MODE_MASK ; 
 unsigned int MAX77843_CHG_OTG_MASK ; 
 int /*<<< orphan*/  MAX77843_CHG_REG_CHG_CNFG_00 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void max77843_charger_set_otg_vbus(struct max77843_muic_info *info,
		 bool on)
{
	struct max77693_dev *max77843 = info->max77843;
	unsigned int cnfg00;

	if (on)
		cnfg00 = MAX77843_CHG_OTG_MASK | MAX77843_CHG_BOOST_MASK;
	else
		cnfg00 = MAX77843_CHG_ENABLE | MAX77843_CHG_BUCK_MASK;

	regmap_update_bits(max77843->regmap_chg, MAX77843_CHG_REG_CHG_CNFG_00,
			   MAX77843_CHG_MODE_MASK, cnfg00);
}
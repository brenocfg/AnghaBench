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
typedef  int u8 ;
struct axp288_chrg_info {int max_cc; int cc; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_CHRG_CTRL1 ; 
 int CHRG_CCCV_CC_BIT_POS ; 
 int CHRG_CCCV_CC_LSB_RES ; 
 int /*<<< orphan*/  CHRG_CCCV_CC_MASK ; 
 int CHRG_CCCV_CC_OFFSET ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int axp288_charger_set_cc(struct axp288_chrg_info *info, int cc)
{
	u8 reg_val;
	int ret;

	if (cc < CHRG_CCCV_CC_OFFSET)
		cc = CHRG_CCCV_CC_OFFSET;
	else if (cc > info->max_cc)
		cc = info->max_cc;

	reg_val = (cc - CHRG_CCCV_CC_OFFSET) / CHRG_CCCV_CC_LSB_RES;
	cc = (reg_val * CHRG_CCCV_CC_LSB_RES) + CHRG_CCCV_CC_OFFSET;
	reg_val = reg_val << CHRG_CCCV_CC_BIT_POS;

	ret = regmap_update_bits(info->regmap,
				AXP20X_CHRG_CTRL1,
				CHRG_CCCV_CC_MASK, reg_val);
	if (ret >= 0)
		info->cc = cc;

	return ret;
}
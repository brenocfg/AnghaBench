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
typedef  int u32 ;
struct mtk_pmic_keys {int /*<<< orphan*/  regmap; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
#define  LP_DISABLE 130 
#define  LP_ONEKEY 129 
#define  LP_TWOKEY 128 
 int MTK_PMIC_HOMEKEY_RST ; 
 int MTK_PMIC_PWRKEY_RST ; 
 int MTK_PMIC_RST_DU_MASK ; 
 int MTK_PMIC_RST_DU_SHIFT ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void mtk_pmic_keys_lp_reset_setup(struct mtk_pmic_keys *keys,
		u32 pmic_rst_reg)
{
	int ret;
	u32 long_press_mode, long_press_debounce;

	ret = of_property_read_u32(keys->dev->of_node,
		"power-off-time-sec", &long_press_debounce);
	if (ret)
		long_press_debounce = 0;

	regmap_update_bits(keys->regmap, pmic_rst_reg,
			   MTK_PMIC_RST_DU_MASK << MTK_PMIC_RST_DU_SHIFT,
			   long_press_debounce << MTK_PMIC_RST_DU_SHIFT);

	ret = of_property_read_u32(keys->dev->of_node,
		"mediatek,long-press-mode", &long_press_mode);
	if (ret)
		long_press_mode = LP_DISABLE;

	switch (long_press_mode) {
	case LP_ONEKEY:
		regmap_update_bits(keys->regmap, pmic_rst_reg,
				   MTK_PMIC_PWRKEY_RST,
				   MTK_PMIC_PWRKEY_RST);
		regmap_update_bits(keys->regmap, pmic_rst_reg,
				   MTK_PMIC_HOMEKEY_RST,
				   0);
		break;
	case LP_TWOKEY:
		regmap_update_bits(keys->regmap, pmic_rst_reg,
				   MTK_PMIC_PWRKEY_RST,
				   MTK_PMIC_PWRKEY_RST);
		regmap_update_bits(keys->regmap, pmic_rst_reg,
				   MTK_PMIC_HOMEKEY_RST,
				   MTK_PMIC_HOMEKEY_RST);
		break;
	case LP_DISABLE:
		regmap_update_bits(keys->regmap, pmic_rst_reg,
				   MTK_PMIC_PWRKEY_RST,
				   0);
		regmap_update_bits(keys->regmap, pmic_rst_reg,
				   MTK_PMIC_HOMEKEY_RST,
				   0);
		break;
	default:
		break;
	}
}
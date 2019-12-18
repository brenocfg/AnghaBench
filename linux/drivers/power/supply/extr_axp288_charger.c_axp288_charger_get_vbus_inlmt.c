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
struct axp288_chrg_info {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_CHRG_BAK_CTRL ; 
#define  CHRG_VBUS_ILIM_100MA 135 
#define  CHRG_VBUS_ILIM_1500MA 134 
#define  CHRG_VBUS_ILIM_2000MA 133 
#define  CHRG_VBUS_ILIM_2500MA 132 
#define  CHRG_VBUS_ILIM_3000MA 131 
#define  CHRG_VBUS_ILIM_3500MA 130 
#define  CHRG_VBUS_ILIM_500MA 129 
#define  CHRG_VBUS_ILIM_900MA 128 
 unsigned int CHRG_VBUS_ILIM_BIT_POS ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int axp288_charger_get_vbus_inlmt(struct axp288_chrg_info *info)
{
	unsigned int val;
	int ret;

	ret = regmap_read(info->regmap, AXP20X_CHRG_BAK_CTRL, &val);
	if (ret < 0)
		return ret;

	val >>= CHRG_VBUS_ILIM_BIT_POS;
	switch (val) {
	case CHRG_VBUS_ILIM_100MA:
		return 100000;
	case CHRG_VBUS_ILIM_500MA:
		return 500000;
	case CHRG_VBUS_ILIM_900MA:
		return 900000;
	case CHRG_VBUS_ILIM_1500MA:
		return 1500000;
	case CHRG_VBUS_ILIM_2000MA:
		return 2000000;
	case CHRG_VBUS_ILIM_2500MA:
		return 2500000;
	case CHRG_VBUS_ILIM_3000MA:
		return 3000000;
	case CHRG_VBUS_ILIM_3500MA:
		return 3500000;
	default:
		/* All b1xxx values map to 4000 mA */
		return 4000000;
	}
}
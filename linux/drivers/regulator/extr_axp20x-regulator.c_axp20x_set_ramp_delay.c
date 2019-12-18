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
struct regulator_dev {int dummy; } ;
struct axp20x_dev {int variant; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
#define  AXP209_ID 128 
 int AXP20X_DCDC2 ; 
 int AXP20X_DCDC2_LDO3_V_RAMP ; 
 int AXP20X_DCDC2_LDO3_V_RAMP_DCDC2_EN ; 
 int AXP20X_DCDC2_LDO3_V_RAMP_DCDC2_EN_MASK ; 
 int AXP20X_DCDC2_LDO3_V_RAMP_DCDC2_RATE_MASK ; 
 int AXP20X_DCDC2_LDO3_V_RAMP_LDO3_EN ; 
 int AXP20X_DCDC2_LDO3_V_RAMP_LDO3_EN_MASK ; 
 int AXP20X_DCDC2_LDO3_V_RAMP_LDO3_RATE (int) ; 
 int AXP20X_DCDC2_LDO3_V_RAMP_LDO3_RATE_MASK ; 
 int AXP20X_LDO3 ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 int* axp209_dcdc2_ldo3_slew_rates ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct axp20x_dev* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int axp20x_set_ramp_delay(struct regulator_dev *rdev, int ramp)
{
	struct axp20x_dev *axp20x = rdev_get_drvdata(rdev);
	int id = rdev_get_id(rdev);
	u8 reg, mask, enable, cfg = 0xff;
	const int *slew_rates;
	int rate_count = 0;

	switch (axp20x->variant) {
	case AXP209_ID:
		if (id == AXP20X_DCDC2) {
			slew_rates = axp209_dcdc2_ldo3_slew_rates;
			rate_count = ARRAY_SIZE(axp209_dcdc2_ldo3_slew_rates);
			reg = AXP20X_DCDC2_LDO3_V_RAMP;
			mask = AXP20X_DCDC2_LDO3_V_RAMP_DCDC2_RATE_MASK |
			       AXP20X_DCDC2_LDO3_V_RAMP_DCDC2_EN_MASK;
			enable = (ramp > 0) ?
				 AXP20X_DCDC2_LDO3_V_RAMP_DCDC2_EN :
				 !AXP20X_DCDC2_LDO3_V_RAMP_DCDC2_EN;
			break;
		}

		if (id == AXP20X_LDO3) {
			slew_rates = axp209_dcdc2_ldo3_slew_rates;
			rate_count = ARRAY_SIZE(axp209_dcdc2_ldo3_slew_rates);
			reg = AXP20X_DCDC2_LDO3_V_RAMP;
			mask = AXP20X_DCDC2_LDO3_V_RAMP_LDO3_RATE_MASK |
			       AXP20X_DCDC2_LDO3_V_RAMP_LDO3_EN_MASK;
			enable = (ramp > 0) ?
				 AXP20X_DCDC2_LDO3_V_RAMP_LDO3_EN :
				 !AXP20X_DCDC2_LDO3_V_RAMP_LDO3_EN;
			break;
		}

		if (rate_count > 0)
			break;

		/* fall through */
	default:
		/* Not supported for this regulator */
		return -ENOTSUPP;
	}

	if (ramp == 0) {
		cfg = enable;
	} else {
		int i;

		for (i = 0; i < rate_count; i++) {
			if (ramp <= slew_rates[i])
				cfg = AXP20X_DCDC2_LDO3_V_RAMP_LDO3_RATE(i);
			else
				break;
		}

		if (cfg == 0xff) {
			dev_err(axp20x->dev, "unsupported ramp value %d", ramp);
			return -EINVAL;
		}

		cfg |= enable;
	}

	return regmap_update_bits(axp20x->regmap, reg, mask, cfg);
}
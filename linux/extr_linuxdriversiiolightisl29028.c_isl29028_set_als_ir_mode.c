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
struct isl29028_chip {int als_ir_mode; int /*<<< orphan*/  regmap; int /*<<< orphan*/  lux_scale; } ;
typedef  enum isl29028_als_ir_mode { ____Placeholder_isl29028_als_ir_mode } isl29028_als_ir_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ISL29028_CONF_ALS_DIS ; 
 int /*<<< orphan*/  ISL29028_CONF_ALS_EN ; 
 int /*<<< orphan*/  ISL29028_CONF_ALS_EN_MASK ; 
 int /*<<< orphan*/  ISL29028_CONF_ALS_IR_MODE_ALS ; 
 int /*<<< orphan*/  ISL29028_CONF_ALS_IR_MODE_IR ; 
 int /*<<< orphan*/  ISL29028_CONF_ALS_IR_MODE_MASK ; 
 int /*<<< orphan*/  ISL29028_CONF_ALS_RANGE_HIGH_LUX ; 
 int /*<<< orphan*/  ISL29028_CONF_ALS_RANGE_MASK ; 
 int /*<<< orphan*/  ISL29028_CONV_TIME_MS ; 
#define  ISL29028_MODE_ALS 130 
#define  ISL29028_MODE_IR 129 
#define  ISL29028_MODE_NONE 128 
 int /*<<< orphan*/  ISL29028_REG_CONFIGURE ; 
 int isl29028_set_als_scale (struct isl29028_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isl29028_set_als_ir_mode(struct isl29028_chip *chip,
				    enum isl29028_als_ir_mode mode)
{
	int ret;

	if (chip->als_ir_mode == mode)
		return 0;

	ret = isl29028_set_als_scale(chip, chip->lux_scale);
	if (ret < 0)
		return ret;

	switch (mode) {
	case ISL29028_MODE_ALS:
		ret = regmap_update_bits(chip->regmap, ISL29028_REG_CONFIGURE,
					 ISL29028_CONF_ALS_IR_MODE_MASK,
					 ISL29028_CONF_ALS_IR_MODE_ALS);
		if (ret < 0)
			return ret;

		ret = regmap_update_bits(chip->regmap, ISL29028_REG_CONFIGURE,
					 ISL29028_CONF_ALS_RANGE_MASK,
					 ISL29028_CONF_ALS_RANGE_HIGH_LUX);
		break;
	case ISL29028_MODE_IR:
		ret = regmap_update_bits(chip->regmap, ISL29028_REG_CONFIGURE,
					 ISL29028_CONF_ALS_IR_MODE_MASK,
					 ISL29028_CONF_ALS_IR_MODE_IR);
		break;
	case ISL29028_MODE_NONE:
		return regmap_update_bits(chip->regmap, ISL29028_REG_CONFIGURE,
					  ISL29028_CONF_ALS_EN_MASK,
					  ISL29028_CONF_ALS_DIS);
	}

	if (ret < 0)
		return ret;

	/* Enable the ALS/IR */
	ret = regmap_update_bits(chip->regmap, ISL29028_REG_CONFIGURE,
				 ISL29028_CONF_ALS_EN_MASK,
				 ISL29028_CONF_ALS_EN);
	if (ret < 0)
		return ret;

	/* Need to wait for conversion time if ALS/IR mode enabled */
	msleep(ISL29028_CONV_TIME_MS);

	chip->als_ir_mode = mode;

	return 0;
}
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
struct max77693_haptic {int dev_type; int type; int mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap_haptic; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX77693_CONFIG2_HTYP ; 
 int MAX77693_CONFIG2_MEN ; 
 int MAX77693_CONFIG2_MODE ; 
 int MAX77693_HAPTIC_PWM_DIVISOR_128 ; 
 unsigned int MAX77693_HAPTIC_REG_CONFIG2 ; 
 unsigned int MAX77843_HAP_REG_MCONFIG ; 
 int MCONFIG_MEN_SHIFT ; 
 int MCONFIG_MODE_SHIFT ; 
#define  TYPE_MAX77693 129 
#define  TYPE_MAX77843 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int max77693_haptic_configure(struct max77693_haptic *haptic,
				     bool enable)
{
	unsigned int value, config_reg;
	int error;

	switch (haptic->dev_type) {
	case TYPE_MAX77693:
		value = ((haptic->type << MAX77693_CONFIG2_MODE) |
			(enable << MAX77693_CONFIG2_MEN) |
			(haptic->mode << MAX77693_CONFIG2_HTYP) |
			MAX77693_HAPTIC_PWM_DIVISOR_128);
		config_reg = MAX77693_HAPTIC_REG_CONFIG2;
		break;
	case TYPE_MAX77843:
		value = (haptic->type << MCONFIG_MODE_SHIFT) |
			(enable << MCONFIG_MEN_SHIFT) |
			MAX77693_HAPTIC_PWM_DIVISOR_128;
		config_reg = MAX77843_HAP_REG_MCONFIG;
		break;
	default:
		return -EINVAL;
	}

	error = regmap_write(haptic->regmap_haptic,
			     config_reg, value);
	if (error) {
		dev_err(haptic->dev,
			"failed to update haptic config: %d\n", error);
		return error;
	}

	return 0;
}
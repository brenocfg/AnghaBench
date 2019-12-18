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
struct regulator_dev {int dummy; } ;
struct max8973_chip {int curr_vout_reg; int curr_gpio_val; unsigned int* curr_vout_val; int /*<<< orphan*/  dvs_gpio; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX8973_VOUT_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int find_voltage_set_register (struct max8973_chip*,unsigned int,int*,int*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 struct max8973_chip* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int max8973_dcdc_set_voltage_sel(struct regulator_dev *rdev,
	     unsigned vsel)
{
	struct max8973_chip *max = rdev_get_drvdata(rdev);
	int ret;
	bool found = false;
	int vout_reg = max->curr_vout_reg;
	int gpio_val = max->curr_gpio_val;

	/*
	 * If gpios are available to select the VOUT register then least
	 * recently used register for new configuration.
	 */
	if (gpio_is_valid(max->dvs_gpio))
		found = find_voltage_set_register(max, vsel,
					&vout_reg, &gpio_val);

	if (!found) {
		ret = regmap_update_bits(max->regmap, vout_reg,
					MAX8973_VOUT_MASK, vsel);
		if (ret < 0) {
			dev_err(max->dev, "register %d update failed, err %d\n",
				 vout_reg, ret);
			return ret;
		}
		max->curr_vout_reg = vout_reg;
		max->curr_vout_val[gpio_val] = vsel;
	}

	/* Select proper VOUT register vio gpios */
	if (gpio_is_valid(max->dvs_gpio)) {
		gpio_set_value_cansleep(max->dvs_gpio, gpio_val & 0x1);
		max->curr_gpio_val = gpio_val;
	}
	return 0;
}
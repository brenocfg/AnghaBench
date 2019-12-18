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
struct da9052 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_GPIO_14_15_REG ; 
 int /*<<< orphan*/  DA9052_MASK_LOWER_NIBBLE ; 
 int /*<<< orphan*/  DA9052_MASK_UPPER_NIBBLE ; 
 unsigned char DA9052_NIBBLE_SHIFT ; 
 unsigned char DA9052_OPENDRAIN_OUTPUT ; 
 unsigned char DA9052_SET_HIGH_LVL_OUTPUT ; 
 int da9052_reg_update (struct da9052*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int da9052_configure_leds(struct da9052 *da9052)
{
	int error;
	unsigned char register_value = DA9052_OPENDRAIN_OUTPUT
				       | DA9052_SET_HIGH_LVL_OUTPUT;

	error = da9052_reg_update(da9052, DA9052_GPIO_14_15_REG,
				  DA9052_MASK_LOWER_NIBBLE,
				  register_value);

	if (error < 0) {
		dev_err(da9052->dev, "Failed to write GPIO 14-15 reg, %d\n",
			error);
		return error;
	}

	error = da9052_reg_update(da9052, DA9052_GPIO_14_15_REG,
				  DA9052_MASK_UPPER_NIBBLE,
				  register_value << DA9052_NIBBLE_SHIFT);
	if (error < 0)
		dev_err(da9052->dev, "Failed to write GPIO 14-15 reg, %d\n",
			error);

	return error;
}
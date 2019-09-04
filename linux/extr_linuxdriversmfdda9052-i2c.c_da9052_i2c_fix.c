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
struct da9052 {int chip_id; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
#define  DA9052 132 
 int /*<<< orphan*/  DA9052_PARK_REGISTER ; 
#define  DA9053_AA 131 
#define  DA9053_BA 130 
#define  DA9053_BB 129 
#define  DA9053_BC 128 
 int /*<<< orphan*/  i2c_safe_reg (unsigned char) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int da9052_i2c_fix(struct da9052 *da9052, unsigned char reg)
{
	int val;

	switch (da9052->chip_id) {
	case DA9052:
	case DA9053_AA:
	case DA9053_BA:
	case DA9053_BB:
		/* A dummy read to a safe register address. */
		if (!i2c_safe_reg(reg))
			return regmap_read(da9052->regmap,
					   DA9052_PARK_REGISTER,
					   &val);
		break;
	case DA9053_BC:
	default:
		/*
		 * For other chips parking of I2C register
		 * to a safe place is not required.
		 */
		break;
	}

	return 0;
}
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
struct regmap {int dummy; } ;

/* Variables and functions */
 unsigned int BMI160_DRDY_INT_EN ; 
 int /*<<< orphan*/  BMI160_NORMAL_WRITE_USLEEP ; 
 int /*<<< orphan*/  BMI160_REG_INT_EN ; 
 int bmi160_write_conf_reg (struct regmap*,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

int bmi160_enable_irq(struct regmap *regmap, bool enable)
{
	unsigned int enable_bit = 0;

	if (enable)
		enable_bit = BMI160_DRDY_INT_EN;

	return bmi160_write_conf_reg(regmap, BMI160_REG_INT_EN,
				     BMI160_DRDY_INT_EN, enable_bit,
				     BMI160_NORMAL_WRITE_USLEEP);
}
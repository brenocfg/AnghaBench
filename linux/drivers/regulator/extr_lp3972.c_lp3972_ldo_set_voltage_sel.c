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
struct lp3972 {int dummy; } ;

/* Variables and functions */
#define  LP3972_LDO1 129 
#define  LP3972_LDO5 128 
 int LP3972_LDO_VOL_CHANGE_SHIFT (int) ; 
 int /*<<< orphan*/  LP3972_LDO_VOL_CONTR_REG (int) ; 
 int LP3972_LDO_VOL_CONTR_SHIFT (int) ; 
 int LP3972_LDO_VOL_MASK (int) ; 
 int LP3972_VOL_CHANGE_FLAG_GO ; 
 int LP3972_VOL_CHANGE_FLAG_MASK ; 
 int /*<<< orphan*/  LP3972_VOL_CHANGE_REG ; 
 int lp3972_set_bits (struct lp3972*,int /*<<< orphan*/ ,int,int) ; 
 struct lp3972* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int lp3972_ldo_set_voltage_sel(struct regulator_dev *dev,
				      unsigned int selector)
{
	struct lp3972 *lp3972 = rdev_get_drvdata(dev);
	int ldo = rdev_get_id(dev) - LP3972_LDO1;
	int shift, ret;

	shift = LP3972_LDO_VOL_CONTR_SHIFT(ldo);
	ret = lp3972_set_bits(lp3972, LP3972_LDO_VOL_CONTR_REG(ldo),
		LP3972_LDO_VOL_MASK(ldo) << shift, selector << shift);

	if (ret)
		return ret;

	/*
	 * LDO1 and LDO5 support voltage control by either target voltage1
	 * or target voltage2 register.
	 * We use target voltage1 register for LDO1 and LDO5 in this driver.
	 * We need to update voltage change control register(0x20) to enable
	 * LDO1 and LDO5 to change to their programmed target values.
	 */
	switch (ldo) {
	case LP3972_LDO1:
	case LP3972_LDO5:
		shift = LP3972_LDO_VOL_CHANGE_SHIFT(ldo);
		ret = lp3972_set_bits(lp3972, LP3972_VOL_CHANGE_REG,
			LP3972_VOL_CHANGE_FLAG_MASK << shift,
			LP3972_VOL_CHANGE_FLAG_GO << shift);
		if (ret)
			return ret;

		ret = lp3972_set_bits(lp3972, LP3972_VOL_CHANGE_REG,
			LP3972_VOL_CHANGE_FLAG_MASK << shift, 0);
		break;
	}

	return ret;
}
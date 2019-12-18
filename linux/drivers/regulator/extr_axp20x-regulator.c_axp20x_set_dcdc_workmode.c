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
typedef  int /*<<< orphan*/  u32 ;
struct regulator_dev {int /*<<< orphan*/  regmap; } ;
struct axp20x_dev {int variant; } ;

/* Variables and functions */
#define  AXP202_ID 135 
#define  AXP209_ID 134 
 int AXP20X_DCDC2 ; 
 int AXP20X_DCDC3 ; 
 unsigned int AXP20X_DCDC_MODE ; 
 unsigned int AXP20X_WORKMODE_DCDC2_MASK ; 
 unsigned int AXP20X_WORKMODE_DCDC3_MASK ; 
#define  AXP221_ID 133 
#define  AXP223_ID 132 
 int AXP22X_DCDC1 ; 
 int AXP22X_DCDC5 ; 
 unsigned int AXP22X_WORKMODE_DCDCX_MASK (int /*<<< orphan*/ ) ; 
 int AXP803_DCDC1 ; 
 int AXP803_DCDC6 ; 
#define  AXP803_ID 131 
 unsigned int AXP806_DCDC_MODE_CTRL2 ; 
#define  AXP806_ID 130 
#define  AXP809_ID 129 
 int AXP813_DCDC1 ; 
 int AXP813_DCDC7 ; 
#define  AXP813_ID 128 
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ffs (unsigned int) ; 
 struct axp20x_dev* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axp20x_set_dcdc_workmode(struct regulator_dev *rdev, int id, u32 workmode)
{
	struct axp20x_dev *axp20x = rdev_get_drvdata(rdev);
	unsigned int reg = AXP20X_DCDC_MODE;
	unsigned int mask;

	switch (axp20x->variant) {
	case AXP202_ID:
	case AXP209_ID:
		if ((id != AXP20X_DCDC2) && (id != AXP20X_DCDC3))
			return -EINVAL;

		mask = AXP20X_WORKMODE_DCDC2_MASK;
		if (id == AXP20X_DCDC3)
			mask = AXP20X_WORKMODE_DCDC3_MASK;

		workmode <<= ffs(mask) - 1;
		break;

	case AXP806_ID:
		/*
		 * AXP806 DCDC regulator IDs have the same range as AXP22X.
		 * (See include/linux/mfd/axp20x.h)
		 */
		reg = AXP806_DCDC_MODE_CTRL2;
		 /* Fall through - to the check below. */
	case AXP221_ID:
	case AXP223_ID:
	case AXP809_ID:
		if (id < AXP22X_DCDC1 || id > AXP22X_DCDC5)
			return -EINVAL;

		mask = AXP22X_WORKMODE_DCDCX_MASK(id - AXP22X_DCDC1);
		workmode <<= id - AXP22X_DCDC1;
		break;

	case AXP803_ID:
		if (id < AXP803_DCDC1 || id > AXP803_DCDC6)
			return -EINVAL;

		mask = AXP22X_WORKMODE_DCDCX_MASK(id - AXP803_DCDC1);
		workmode <<= id - AXP803_DCDC1;
		break;

	case AXP813_ID:
		if (id < AXP813_DCDC1 || id > AXP813_DCDC7)
			return -EINVAL;

		mask = AXP22X_WORKMODE_DCDCX_MASK(id - AXP813_DCDC1);
		workmode <<= id - AXP813_DCDC1;
		break;

	default:
		/* should not happen */
		WARN_ON(1);
		return -EINVAL;
	}

	return regmap_update_bits(rdev->regmap, reg, mask, workmode);
}
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
struct regulator_dev {struct regmap* regmap; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int ACT8945A_DCDC1_SUS ; 
 int ACT8945A_DCDC2_SUS ; 
 int ACT8945A_DCDC3_SUS ; 
#define  ACT8945A_ID_DCDC1 134 
#define  ACT8945A_ID_DCDC2 133 
#define  ACT8945A_ID_DCDC3 132 
#define  ACT8945A_ID_LDO1 131 
#define  ACT8945A_ID_LDO2 130 
#define  ACT8945A_ID_LDO3 129 
#define  ACT8945A_ID_LDO4 128 
 int ACT8945A_LDO1_SUS ; 
 int ACT8945A_LDO2_SUS ; 
 int ACT8945A_LDO3_SUS ; 
 int ACT8945A_LDO4_SUS ; 
 int BIT (int) ; 
 int EINVAL ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int regmap_write (struct regmap*,int,int) ; 

__attribute__((used)) static int act8945a_set_suspend_state(struct regulator_dev *rdev, bool enable)
{
	struct regmap *regmap = rdev->regmap;
	int id = rdev_get_id(rdev);
	int reg, val;

	switch (id) {
	case ACT8945A_ID_DCDC1:
		reg = ACT8945A_DCDC1_SUS;
		val = 0xa8;
		break;
	case ACT8945A_ID_DCDC2:
		reg = ACT8945A_DCDC2_SUS;
		val = 0xa8;
		break;
	case ACT8945A_ID_DCDC3:
		reg = ACT8945A_DCDC3_SUS;
		val = 0xa8;
		break;
	case ACT8945A_ID_LDO1:
		reg = ACT8945A_LDO1_SUS;
		val = 0xe8;
		break;
	case ACT8945A_ID_LDO2:
		reg = ACT8945A_LDO2_SUS;
		val = 0xe8;
		break;
	case ACT8945A_ID_LDO3:
		reg = ACT8945A_LDO3_SUS;
		val = 0xe8;
		break;
	case ACT8945A_ID_LDO4:
		reg = ACT8945A_LDO4_SUS;
		val = 0xe8;
		break;
	default:
		return -EINVAL;
	}

	if (enable)
		val |= BIT(4);

	/*
	 * Ask the PMIC to enable/disable this output when entering hibernate
	 * mode.
	 */
	return regmap_write(regmap, reg, val);
}
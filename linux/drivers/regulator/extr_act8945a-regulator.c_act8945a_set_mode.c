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
struct act8945a_pmic {unsigned int* op_mode; } ;

/* Variables and functions */
 int ACT8945A_DCDC1_CTRL ; 
 int ACT8945A_DCDC2_CTRL ; 
 int ACT8945A_DCDC3_CTRL ; 
#define  ACT8945A_ID_DCDC1 136 
#define  ACT8945A_ID_DCDC2 135 
#define  ACT8945A_ID_DCDC3 134 
#define  ACT8945A_ID_LDO1 133 
#define  ACT8945A_ID_LDO2 132 
#define  ACT8945A_ID_LDO3 131 
#define  ACT8945A_ID_LDO4 130 
 int ACT8945A_LDO1_CTRL ; 
 int ACT8945A_LDO2_CTRL ; 
 int ACT8945A_LDO3_CTRL ; 
 int ACT8945A_LDO4_CTRL ; 
 int BIT (int) ; 
 int EINVAL ; 
#define  REGULATOR_MODE_NORMAL 129 
#define  REGULATOR_MODE_STANDBY 128 
 struct act8945a_pmic* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int regmap_update_bits (struct regmap*,int,int,int) ; 

__attribute__((used)) static int act8945a_set_mode(struct regulator_dev *rdev, unsigned int mode)
{
	struct act8945a_pmic *act8945a = rdev_get_drvdata(rdev);
	struct regmap *regmap = rdev->regmap;
	int id = rdev_get_id(rdev);
	int reg, ret, val = 0;

	switch (id) {
	case ACT8945A_ID_DCDC1:
		reg = ACT8945A_DCDC1_CTRL;
		break;
	case ACT8945A_ID_DCDC2:
		reg = ACT8945A_DCDC2_CTRL;
		break;
	case ACT8945A_ID_DCDC3:
		reg = ACT8945A_DCDC3_CTRL;
		break;
	case ACT8945A_ID_LDO1:
		reg = ACT8945A_LDO1_CTRL;
		break;
	case ACT8945A_ID_LDO2:
		reg = ACT8945A_LDO2_CTRL;
		break;
	case ACT8945A_ID_LDO3:
		reg = ACT8945A_LDO3_CTRL;
		break;
	case ACT8945A_ID_LDO4:
		reg = ACT8945A_LDO4_CTRL;
		break;
	default:
		return -EINVAL;
	}

	switch (mode) {
	case REGULATOR_MODE_STANDBY:
		if (id > ACT8945A_ID_DCDC3)
			val = BIT(5);
		break;
	case REGULATOR_MODE_NORMAL:
		if (id <= ACT8945A_ID_DCDC3)
			val = BIT(5);
		break;
	default:
		return -EINVAL;
	}

	ret = regmap_update_bits(regmap, reg, BIT(5), val);
	if (ret)
		return ret;

	act8945a->op_mode[id] = mode;

	return 0;
}
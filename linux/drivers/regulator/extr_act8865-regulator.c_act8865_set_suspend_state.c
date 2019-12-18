#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {TYPE_1__* desc; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int ACT8865_DCDC1_SUS ; 
 int ACT8865_DCDC2_SUS ; 
 int ACT8865_DCDC3_SUS ; 
#define  ACT8865_ID_DCDC1 134 
#define  ACT8865_ID_DCDC2 133 
#define  ACT8865_ID_DCDC3 132 
#define  ACT8865_ID_LDO1 131 
#define  ACT8865_ID_LDO2 130 
#define  ACT8865_ID_LDO3 129 
#define  ACT8865_ID_LDO4 128 
 int ACT8865_LDO1_SUS ; 
 int ACT8865_LDO2_SUS ; 
 int ACT8865_LDO3_SUS ; 
 int ACT8865_LDO4_SUS ; 
 int BIT (int) ; 
 int EINVAL ; 
 int regmap_write (struct regmap*,int,int) ; 

__attribute__((used)) static int act8865_set_suspend_state(struct regulator_dev *rdev, bool enable)
{
	struct regmap *regmap = rdev->regmap;
	int id = rdev->desc->id, reg, val;

	switch (id) {
	case ACT8865_ID_DCDC1:
		reg = ACT8865_DCDC1_SUS;
		val = 0xa8;
		break;
	case ACT8865_ID_DCDC2:
		reg = ACT8865_DCDC2_SUS;
		val = 0xa8;
		break;
	case ACT8865_ID_DCDC3:
		reg = ACT8865_DCDC3_SUS;
		val = 0xa8;
		break;
	case ACT8865_ID_LDO1:
		reg = ACT8865_LDO1_SUS;
		val = 0xe8;
		break;
	case ACT8865_ID_LDO2:
		reg = ACT8865_LDO2_SUS;
		val = 0xe8;
		break;
	case ACT8865_ID_LDO3:
		reg = ACT8865_LDO3_SUS;
		val = 0xe8;
		break;
	case ACT8865_ID_LDO4:
		reg = ACT8865_LDO4_SUS;
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
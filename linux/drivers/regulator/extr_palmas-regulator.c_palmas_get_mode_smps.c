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
struct palmas_pmic {unsigned int* current_reg_mode; } ;

/* Variables and functions */
 unsigned int PALMAS_SMPS12_CTRL_MODE_ACTIVE_MASK ; 
 unsigned int REGULATOR_MODE_FAST ; 
 unsigned int REGULATOR_MODE_IDLE ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
#define  SMPS_CTRL_MODE_ECO 130 
#define  SMPS_CTRL_MODE_ON 129 
#define  SMPS_CTRL_MODE_PWM 128 
 struct palmas_pmic* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static unsigned int palmas_get_mode_smps(struct regulator_dev *dev)
{
	struct palmas_pmic *pmic = rdev_get_drvdata(dev);
	int id = rdev_get_id(dev);
	unsigned int reg;

	reg = pmic->current_reg_mode[id] & PALMAS_SMPS12_CTRL_MODE_ACTIVE_MASK;

	switch (reg) {
	case SMPS_CTRL_MODE_ON:
		return REGULATOR_MODE_NORMAL;
	case SMPS_CTRL_MODE_ECO:
		return REGULATOR_MODE_IDLE;
	case SMPS_CTRL_MODE_PWM:
		return REGULATOR_MODE_FAST;
	}

	return 0;
}
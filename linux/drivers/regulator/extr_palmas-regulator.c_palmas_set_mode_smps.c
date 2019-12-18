#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {int dummy; } ;
struct palmas_regs_info {int /*<<< orphan*/  ctrl_addr; } ;
struct palmas_pmic_driver_data {struct palmas_regs_info* palmas_regs_info; } ;
struct palmas_pmic {unsigned int* current_reg_mode; TYPE_1__* desc; TYPE_2__* palmas; } ;
struct TYPE_5__ {struct palmas_pmic_driver_data* pmic_ddata; } ;
struct TYPE_4__ {unsigned int enable_val; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int PALMAS_SMPS12_CTRL_MODE_ACTIVE_MASK ; 
#define  REGULATOR_MODE_FAST 130 
#define  REGULATOR_MODE_IDLE 129 
#define  REGULATOR_MODE_NORMAL 128 
 unsigned int SMPS_CTRL_MODE_ECO ; 
 unsigned int SMPS_CTRL_MODE_OFF ; 
 unsigned int SMPS_CTRL_MODE_ON ; 
 unsigned int SMPS_CTRL_MODE_PWM ; 
 int palmas_smps_read (TYPE_2__*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  palmas_smps_write (TYPE_2__*,int /*<<< orphan*/ ,unsigned int) ; 
 struct palmas_pmic* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int palmas_set_mode_smps(struct regulator_dev *dev, unsigned int mode)
{
	int id = rdev_get_id(dev);
	int ret;
	struct palmas_pmic *pmic = rdev_get_drvdata(dev);
	struct palmas_pmic_driver_data *ddata = pmic->palmas->pmic_ddata;
	struct palmas_regs_info *rinfo = &ddata->palmas_regs_info[id];
	unsigned int reg;
	bool rail_enable = true;

	ret = palmas_smps_read(pmic->palmas, rinfo->ctrl_addr, &reg);
	if (ret)
		return ret;

	reg &= ~PALMAS_SMPS12_CTRL_MODE_ACTIVE_MASK;

	if (reg == SMPS_CTRL_MODE_OFF)
		rail_enable = false;

	switch (mode) {
	case REGULATOR_MODE_NORMAL:
		reg |= SMPS_CTRL_MODE_ON;
		break;
	case REGULATOR_MODE_IDLE:
		reg |= SMPS_CTRL_MODE_ECO;
		break;
	case REGULATOR_MODE_FAST:
		reg |= SMPS_CTRL_MODE_PWM;
		break;
	default:
		return -EINVAL;
	}

	pmic->current_reg_mode[id] = reg & PALMAS_SMPS12_CTRL_MODE_ACTIVE_MASK;
	if (rail_enable)
		palmas_smps_write(pmic->palmas, rinfo->ctrl_addr, reg);

	/* Switch the enable value to ensure this is used for enable */
	pmic->desc[id].enable_val = pmic->current_reg_mode[id];

	return 0;
}
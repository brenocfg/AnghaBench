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
typedef  int u16 ;
struct regulator_dev {int dummy; } ;
struct lp3971 {int dummy; } ;

/* Variables and functions */
 int LDO_VOL_CONTR_MASK ; 
 int LDO_VOL_CONTR_SHIFT (int) ; 
 int LP3971_LDO1 ; 
 int /*<<< orphan*/  LP3971_LDO_VOL_CONTR_REG (int) ; 
 int lp3971_reg_read (struct lp3971*,int /*<<< orphan*/ ) ; 
 struct lp3971* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int lp3971_ldo_get_voltage_sel(struct regulator_dev *dev)
{
	struct lp3971 *lp3971 = rdev_get_drvdata(dev);
	int ldo = rdev_get_id(dev) - LP3971_LDO1;
	u16 val, reg;

	reg = lp3971_reg_read(lp3971, LP3971_LDO_VOL_CONTR_REG(ldo));
	val = (reg >> LDO_VOL_CONTR_SHIFT(ldo)) & LDO_VOL_CONTR_MASK;

	return val;
}
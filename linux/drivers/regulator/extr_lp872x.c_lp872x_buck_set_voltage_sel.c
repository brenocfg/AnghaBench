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
typedef  int /*<<< orphan*/  u8 ;
struct regulator_dev {int dummy; } ;
struct lp872x_dvs {int /*<<< orphan*/  gpio; int /*<<< orphan*/  vsel; } ;
struct lp872x {TYPE_1__* pdata; } ;
typedef  enum lp872x_regulator_id { ____Placeholder_lp872x_regulator_id } lp872x_regulator_id ;
struct TYPE_2__ {struct lp872x_dvs* dvs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LP872X_VOUT_M ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp872x_is_valid_buck_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp872x_select_buck_vout_addr (struct lp872x*,int) ; 
 int /*<<< orphan*/  lp872x_set_dvs (struct lp872x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lp872x_update_bits (struct lp872x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct lp872x* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int lp872x_buck_set_voltage_sel(struct regulator_dev *rdev,
					unsigned selector)
{
	struct lp872x *lp = rdev_get_drvdata(rdev);
	enum lp872x_regulator_id buck = rdev_get_id(rdev);
	u8 addr, mask = LP872X_VOUT_M;
	struct lp872x_dvs *dvs = lp->pdata ? lp->pdata->dvs : NULL;

	if (dvs && gpio_is_valid(dvs->gpio))
		lp872x_set_dvs(lp, dvs->vsel, dvs->gpio);

	addr = lp872x_select_buck_vout_addr(lp, buck);
	if (!lp872x_is_valid_buck_addr(addr))
		return -EINVAL;

	return lp872x_update_bits(lp, addr, mask, selector);
}
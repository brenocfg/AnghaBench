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
typedef  int u8 ;
struct regulator_dev {int dummy; } ;
struct lp8788_buck {int /*<<< orphan*/  lp; } ;
typedef  enum lp8788_buck_id { ____Placeholder_lp8788_buck_id } lp8788_buck_id ;

/* Variables and functions */
 int BUCK_FPWM_MASK (int) ; 
 int BUCK_FPWM_SHIFT (int) ; 
 int EINVAL ; 
 int LP8788_AUTO_PWM ; 
 int /*<<< orphan*/  LP8788_BUCK_PWM ; 
 int LP8788_FORCE_PWM ; 
#define  REGULATOR_MODE_FAST 129 
#define  REGULATOR_MODE_NORMAL 128 
 int lp8788_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct lp8788_buck* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int lp8788_buck_set_mode(struct regulator_dev *rdev, unsigned int mode)
{
	struct lp8788_buck *buck = rdev_get_drvdata(rdev);
	enum lp8788_buck_id id = rdev_get_id(rdev);
	u8 mask, val;

	mask = BUCK_FPWM_MASK(id);
	switch (mode) {
	case REGULATOR_MODE_FAST:
		val = LP8788_FORCE_PWM << BUCK_FPWM_SHIFT(id);
		break;
	case REGULATOR_MODE_NORMAL:
		val = LP8788_AUTO_PWM << BUCK_FPWM_SHIFT(id);
		break;
	default:
		return -EINVAL;
	}

	return lp8788_update_bits(buck->lp, LP8788_BUCK_PWM, mask, val);
}
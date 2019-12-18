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
struct rpmh_vreg {unsigned int voltage_selector; int /*<<< orphan*/  enabled; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int _rpmh_regulator_vrm_set_voltage_sel (struct regulator_dev*,unsigned int,int) ; 
 struct rpmh_vreg* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int rpmh_regulator_vrm_set_voltage_sel(struct regulator_dev *rdev,
					unsigned int selector)
{
	struct rpmh_vreg *vreg = rdev_get_drvdata(rdev);

	if (vreg->enabled == -EINVAL) {
		/*
		 * Cache the voltage and send it later when the regulator is
		 * enabled or disabled.
		 */
		vreg->voltage_selector = selector;
		return 0;
	}

	return _rpmh_regulator_vrm_set_voltage_sel(rdev, selector,
					selector > vreg->voltage_selector);
}
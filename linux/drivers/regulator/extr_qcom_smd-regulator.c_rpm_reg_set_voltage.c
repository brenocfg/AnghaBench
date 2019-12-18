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
struct qcom_rpm_reg {int uV; int uv_updated; } ;

/* Variables and functions */
 struct qcom_rpm_reg* rdev_get_drvdata (struct regulator_dev*) ; 
 int rpm_reg_write_active (struct qcom_rpm_reg*) ; 

__attribute__((used)) static int rpm_reg_set_voltage(struct regulator_dev *rdev,
			       int min_uV,
			       int max_uV,
			       unsigned *selector)
{
	struct qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);
	int ret;
	int old_uV = vreg->uV;

	vreg->uV = min_uV;
	vreg->uv_updated = 1;

	ret = rpm_reg_write_active(vreg);
	if (ret)
		vreg->uV = old_uV;

	return ret;
}
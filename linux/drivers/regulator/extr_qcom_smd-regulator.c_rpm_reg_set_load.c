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
typedef  int u32 ;
struct regulator_dev {int dummy; } ;
struct qcom_rpm_reg {int load; int load_updated; } ;

/* Variables and functions */
 struct qcom_rpm_reg* rdev_get_drvdata (struct regulator_dev*) ; 
 int rpm_reg_write_active (struct qcom_rpm_reg*) ; 

__attribute__((used)) static int rpm_reg_set_load(struct regulator_dev *rdev, int load_uA)
{
	struct qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);
	u32 old_load = vreg->load;
	int ret;

	vreg->load = load_uA;
	vreg->load_updated = 1;
	ret = rpm_reg_write_active(vreg);
	if (ret)
		vreg->load = old_load;

	return ret;
}
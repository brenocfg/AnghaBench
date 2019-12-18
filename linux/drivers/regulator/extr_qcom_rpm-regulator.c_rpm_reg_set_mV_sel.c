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
struct request_member {scalar_t__ mask; } ;
struct rpm_reg_parts {struct request_member mV; } ;
struct regulator_dev {int dummy; } ;
struct qcom_rpm_reg {int uV; int /*<<< orphan*/  lock; scalar_t__ is_enabled; struct rpm_reg_parts* parts; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct qcom_rpm_reg* rdev_get_drvdata (struct regulator_dev*) ; 
 int regulator_list_voltage_linear_range (struct regulator_dev*,unsigned int) ; 
 int rpm_reg_write (struct qcom_rpm_reg*,struct request_member const*,int) ; 

__attribute__((used)) static int rpm_reg_set_mV_sel(struct regulator_dev *rdev,
			      unsigned selector)
{
	struct qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);
	const struct rpm_reg_parts *parts = vreg->parts;
	const struct request_member *req = &parts->mV;
	int ret = 0;
	int uV;

	if (req->mask == 0)
		return -EINVAL;

	uV = regulator_list_voltage_linear_range(rdev, selector);
	if (uV < 0)
		return uV;

	mutex_lock(&vreg->lock);
	if (vreg->is_enabled)
		ret = rpm_reg_write(vreg, req, uV / 1000);

	if (!ret)
		vreg->uV = uV;
	mutex_unlock(&vreg->lock);

	return ret;
}
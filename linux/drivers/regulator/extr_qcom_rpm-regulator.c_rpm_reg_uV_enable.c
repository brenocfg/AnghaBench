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
struct rpm_reg_parts {struct request_member uV; } ;
struct regulator_dev {int dummy; } ;
struct qcom_rpm_reg {int is_enabled; int /*<<< orphan*/  lock; int /*<<< orphan*/  uV; struct rpm_reg_parts* parts; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct qcom_rpm_reg* rdev_get_drvdata (struct regulator_dev*) ; 
 int rpm_reg_write (struct qcom_rpm_reg*,struct request_member const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpm_reg_uV_enable(struct regulator_dev *rdev)
{
	struct qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);
	const struct rpm_reg_parts *parts = vreg->parts;
	const struct request_member *req = &parts->uV;
	int ret;

	if (req->mask == 0)
		return -EINVAL;

	mutex_lock(&vreg->lock);
	ret = rpm_reg_write(vreg, req, vreg->uV);
	if (!ret)
		vreg->is_enabled = 1;
	mutex_unlock(&vreg->lock);

	return ret;
}
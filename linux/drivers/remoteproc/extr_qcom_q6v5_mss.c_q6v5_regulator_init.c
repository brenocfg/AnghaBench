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
struct reg_info {int /*<<< orphan*/  uA; int /*<<< orphan*/  uV; int /*<<< orphan*/  reg; } ;
struct qcom_mss_reg_res {int /*<<< orphan*/  uA; int /*<<< orphan*/  uV; scalar_t__ supply; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  devm_regulator_get (struct device*,scalar_t__) ; 

__attribute__((used)) static int q6v5_regulator_init(struct device *dev, struct reg_info *regs,
			       const struct qcom_mss_reg_res *reg_res)
{
	int rc;
	int i;

	if (!reg_res)
		return 0;

	for (i = 0; reg_res[i].supply; i++) {
		regs[i].reg = devm_regulator_get(dev, reg_res[i].supply);
		if (IS_ERR(regs[i].reg)) {
			rc = PTR_ERR(regs[i].reg);
			if (rc != -EPROBE_DEFER)
				dev_err(dev, "Failed to get %s\n regulator",
					reg_res[i].supply);
			return rc;
		}

		regs[i].uV = reg_res[i].uV;
		regs[i].uA = reg_res[i].uA;
	}

	return i;
}
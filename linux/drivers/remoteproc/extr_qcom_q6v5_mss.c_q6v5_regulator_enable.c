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
struct reg_info {scalar_t__ uV; scalar_t__ uA; int /*<<< orphan*/  reg; } ;
struct q6v5 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int regulator_set_load (int /*<<< orphan*/ ,scalar_t__) ; 
 int regulator_set_voltage (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int q6v5_regulator_enable(struct q6v5 *qproc,
				 struct reg_info *regs, int count)
{
	int ret;
	int i;

	for (i = 0; i < count; i++) {
		if (regs[i].uV > 0) {
			ret = regulator_set_voltage(regs[i].reg,
					regs[i].uV, INT_MAX);
			if (ret) {
				dev_err(qproc->dev,
					"Failed to request voltage for %d.\n",
						i);
				goto err;
			}
		}

		if (regs[i].uA > 0) {
			ret = regulator_set_load(regs[i].reg,
						 regs[i].uA);
			if (ret < 0) {
				dev_err(qproc->dev,
					"Failed to set regulator mode\n");
				goto err;
			}
		}

		ret = regulator_enable(regs[i].reg);
		if (ret) {
			dev_err(qproc->dev, "Regulator enable failed\n");
			goto err;
		}
	}

	return 0;
err:
	for (; i >= 0; i--) {
		if (regs[i].uV > 0)
			regulator_set_voltage(regs[i].reg, 0, INT_MAX);

		if (regs[i].uA > 0)
			regulator_set_load(regs[i].reg, 0);

		regulator_disable(regs[i].reg);
	}

	return ret;
}
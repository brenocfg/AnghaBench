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
struct samsung_retention_ctrl {int nr_regs; int /*<<< orphan*/  value; int /*<<< orphan*/ * regs; scalar_t__ refcnt; struct regmap* priv; } ;
struct samsung_pinctrl_drv_data {struct samsung_retention_ctrl* retention_ctrl; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (scalar_t__) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_retention_disable(struct samsung_pinctrl_drv_data *drvdata)
{
	struct samsung_retention_ctrl *ctrl = drvdata->retention_ctrl;
	struct regmap *pmu_regs = ctrl->priv;
	int i;

	if (ctrl->refcnt && !atomic_dec_and_test(ctrl->refcnt))
		return;

	for (i = 0; i < ctrl->nr_regs; i++)
		regmap_write(pmu_regs, ctrl->regs[i], ctrl->value);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct exynos_pmu_data {int /*<<< orphan*/  (* powerdown_conf_extra ) (int) ;TYPE_1__* pmu_config; int /*<<< orphan*/  (* powerdown_conf ) (int) ;} ;
typedef  enum sys_powerdown { ____Placeholder_sys_powerdown } sys_powerdown ;
struct TYPE_4__ {struct exynos_pmu_data* pmu_data; } ;
struct TYPE_3__ {scalar_t__ offset; int /*<<< orphan*/ * val; } ;

/* Variables and functions */
 scalar_t__ PMU_TABLE_END ; 
 TYPE_2__* pmu_context ; 
 int /*<<< orphan*/  pmu_raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 

void exynos_sys_powerdown_conf(enum sys_powerdown mode)
{
	unsigned int i;
	const struct exynos_pmu_data *pmu_data;

	if (!pmu_context || !pmu_context->pmu_data)
		return;

	pmu_data = pmu_context->pmu_data;

	if (pmu_data->powerdown_conf)
		pmu_data->powerdown_conf(mode);

	if (pmu_data->pmu_config) {
		for (i = 0; (pmu_data->pmu_config[i].offset != PMU_TABLE_END); i++)
			pmu_raw_writel(pmu_data->pmu_config[i].val[mode],
					pmu_data->pmu_config[i].offset);
	}

	if (pmu_data->powerdown_conf_extra)
		pmu_data->powerdown_conf_extra(mode);
}
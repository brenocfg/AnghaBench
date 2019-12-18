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
struct rockchip_pmu {TYPE_1__* info; int /*<<< orphan*/  regmap; } ;
struct rockchip_pm_domain {TYPE_2__* info; struct rockchip_pmu* pmu; } ;
struct TYPE_4__ {unsigned int status_mask; } ;
struct TYPE_3__ {int /*<<< orphan*/  status_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  rockchip_pmu_domain_is_idle (struct rockchip_pm_domain*) ; 

__attribute__((used)) static bool rockchip_pmu_domain_is_on(struct rockchip_pm_domain *pd)
{
	struct rockchip_pmu *pmu = pd->pmu;
	unsigned int val;

	/* check idle status for idle-only domains */
	if (pd->info->status_mask == 0)
		return !rockchip_pmu_domain_is_idle(pd);

	regmap_read(pmu->regmap, pmu->info->status_offset, &val);

	/* 1'b0: power on, 1'b1: power off */
	return !(val & pd->info->status_mask);
}
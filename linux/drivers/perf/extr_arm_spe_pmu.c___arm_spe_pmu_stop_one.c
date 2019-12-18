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
struct arm_spe_pmu {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __arm_spe_pmu_reset_local () ; 
 int /*<<< orphan*/  disable_percpu_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __arm_spe_pmu_stop_one(void *info)
{
	struct arm_spe_pmu *spe_pmu = info;

	disable_percpu_irq(spe_pmu->irq);
	__arm_spe_pmu_reset_local();
}
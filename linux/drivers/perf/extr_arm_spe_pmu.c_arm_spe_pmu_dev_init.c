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
struct arm_spe_pmu {int features; int /*<<< orphan*/  handle; int /*<<< orphan*/  irq; int /*<<< orphan*/  hotplug_node; int /*<<< orphan*/  supported_cpus; } ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRVNAME ; 
 int ENXIO ; 
 int SPE_PMU_FEAT_DEV_PROBED ; 
 int /*<<< orphan*/  __arm_spe_pmu_dev_probe ; 
 int /*<<< orphan*/  arm_spe_pmu_irq_handler ; 
 int /*<<< orphan*/  arm_spe_pmu_online ; 
 int cpuhp_state_add_instance (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_percpu_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_percpu_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smp_call_function_any (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct arm_spe_pmu*,int) ; 

__attribute__((used)) static int arm_spe_pmu_dev_init(struct arm_spe_pmu *spe_pmu)
{
	int ret;
	cpumask_t *mask = &spe_pmu->supported_cpus;

	/* Make sure we probe the hardware on a relevant CPU */
	ret = smp_call_function_any(mask,  __arm_spe_pmu_dev_probe, spe_pmu, 1);
	if (ret || !(spe_pmu->features & SPE_PMU_FEAT_DEV_PROBED))
		return -ENXIO;

	/* Request our PPIs (note that the IRQ is still disabled) */
	ret = request_percpu_irq(spe_pmu->irq, arm_spe_pmu_irq_handler, DRVNAME,
				 spe_pmu->handle);
	if (ret)
		return ret;

	/*
	 * Register our hotplug notifier now so we don't miss any events.
	 * This will enable the IRQ for any supported CPUs that are already
	 * up.
	 */
	ret = cpuhp_state_add_instance(arm_spe_pmu_online,
				       &spe_pmu->hotplug_node);
	if (ret)
		free_percpu_irq(spe_pmu->irq, spe_pmu->handle);

	return ret;
}
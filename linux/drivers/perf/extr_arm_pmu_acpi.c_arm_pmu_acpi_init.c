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

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_AP_PERF_ARM_ACPI_STARTING ; 
 scalar_t__ acpi_disabled ; 
 int /*<<< orphan*/  arm_pmu_acpi_cpu_starting ; 
 int arm_pmu_acpi_parse_irqs () ; 
 int /*<<< orphan*/  arm_spe_acpi_register_device () ; 
 int cpuhp_setup_state (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int arm_pmu_acpi_init(void)
{
	int ret;

	if (acpi_disabled)
		return 0;

	arm_spe_acpi_register_device();

	ret = arm_pmu_acpi_parse_irqs();
	if (ret)
		return ret;

	ret = cpuhp_setup_state(CPUHP_AP_PERF_ARM_ACPI_STARTING,
				"perf/arm/pmu_acpi:starting",
				arm_pmu_acpi_cpu_starting, NULL);

	return ret;
}
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
 int /*<<< orphan*/  CPUFREQ_POLICY_NOTIFIER ; 
 int PPC_REGISTERED ; 
 int /*<<< orphan*/  acpi_ppc_notifier_block ; 
 int acpi_processor_ppc_status ; 
 int /*<<< orphan*/  cpufreq_unregister_notifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void acpi_processor_ppc_exit(void)
{
	if (acpi_processor_ppc_status & PPC_REGISTERED)
		cpufreq_unregister_notifier(&acpi_ppc_notifier_block,
					    CPUFREQ_POLICY_NOTIFIER);

	acpi_processor_ppc_status &= ~PPC_REGISTERED;
}
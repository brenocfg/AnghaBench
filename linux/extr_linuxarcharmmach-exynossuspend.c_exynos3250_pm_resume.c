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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ ARM_CPU_PART_CORTEX_A9 ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  S5P_CENTRAL_SEQ_OPTION ; 
 int /*<<< orphan*/  S5P_INFORM1 ; 
 int S5P_USE_STANDBY_WFI_ALL ; 
 int /*<<< orphan*/  call_firmware_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_cpu_restore_register () ; 
 scalar_t__ exynos_pm_central_resume () ; 
 int /*<<< orphan*/  pmu_raw_writel (int,int /*<<< orphan*/ ) ; 
 scalar_t__ read_cpuid_part () ; 
 int /*<<< orphan*/  resume ; 

__attribute__((used)) static void exynos3250_pm_resume(void)
{
	u32 cpuid = read_cpuid_part();

	if (exynos_pm_central_resume())
		goto early_wakeup;

	pmu_raw_writel(S5P_USE_STANDBY_WFI_ALL, S5P_CENTRAL_SEQ_OPTION);

	if (call_firmware_op(resume) == -ENOSYS
	    && cpuid == ARM_CPU_PART_CORTEX_A9)
		exynos_cpu_restore_register();

early_wakeup:

	/* Clear SLEEP mode set in INFORM1 */
	pmu_raw_writel(0x0, S5P_INFORM1);
}
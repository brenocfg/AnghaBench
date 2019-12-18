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
 int /*<<< orphan*/  SYS_PMBLIMITR_EL1 ; 
 int /*<<< orphan*/  SYS_PMSCR_EL1 ; 
 int /*<<< orphan*/  dsb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isb () ; 
 int /*<<< orphan*/  nsh ; 
 int /*<<< orphan*/  psb_csync () ; 
 int /*<<< orphan*/  write_sysreg_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arm_spe_pmu_disable_and_drain_local(void)
{
	/* Disable profiling at EL0 and EL1 */
	write_sysreg_s(0, SYS_PMSCR_EL1);
	isb();

	/* Drain any buffered data */
	psb_csync();
	dsb(nsh);

	/* Disable the profiling buffer */
	write_sysreg_s(0, SYS_PMBLIMITR_EL1);
	isb();
}
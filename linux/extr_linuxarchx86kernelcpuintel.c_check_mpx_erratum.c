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
struct cpuinfo_x86 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_MPX ; 
 int /*<<< orphan*/  X86_FEATURE_SMEP ; 
 scalar_t__ cpu_has (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 scalar_t__ forcempx ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  setup_clear_cpu_cap (int /*<<< orphan*/ ) ; 

void check_mpx_erratum(struct cpuinfo_x86 *c)
{
	if (forcempx)
		return;
	/*
	 * Turn off the MPX feature on CPUs where SMEP is not
	 * available or disabled.
	 *
	 * Works around Intel Erratum SKD046: "Branch Instructions
	 * May Initialize MPX Bound Registers Incorrectly".
	 *
	 * This might falsely disable MPX on systems without
	 * SMEP, like Atom processors without SMEP.  But there
	 * is no such hardware known at the moment.
	 */
	if (cpu_has(c, X86_FEATURE_MPX) && !cpu_has(c, X86_FEATURE_SMEP)) {
		setup_clear_cpu_cap(X86_FEATURE_MPX);
		pr_warn("x86/mpx: Disabling MPX since SMEP not present\n");
	}
}
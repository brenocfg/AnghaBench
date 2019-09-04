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
 int /*<<< orphan*/  X86_FEATURE_AMD_IBPB ; 
 int /*<<< orphan*/  X86_FEATURE_AMD_IBRS ; 
 int /*<<< orphan*/  X86_FEATURE_AMD_SSBD ; 
 int /*<<< orphan*/  X86_FEATURE_AMD_STIBP ; 
 int /*<<< orphan*/  X86_FEATURE_IBPB ; 
 int /*<<< orphan*/  X86_FEATURE_IBRS ; 
 int /*<<< orphan*/  X86_FEATURE_INTEL_STIBP ; 
 int /*<<< orphan*/  X86_FEATURE_MSR_SPEC_CTRL ; 
 int /*<<< orphan*/  X86_FEATURE_SPEC_CTRL ; 
 int /*<<< orphan*/  X86_FEATURE_SPEC_CTRL_SSBD ; 
 int /*<<< orphan*/  X86_FEATURE_SSBD ; 
 int /*<<< orphan*/  X86_FEATURE_STIBP ; 
 int /*<<< orphan*/  X86_FEATURE_VIRT_SSBD ; 
 int /*<<< orphan*/  clear_cpu_cap (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_has (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cpu_cap (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_speculation_control(struct cpuinfo_x86 *c)
{
	/*
	 * The Intel SPEC_CTRL CPUID bit implies IBRS and IBPB support,
	 * and they also have a different bit for STIBP support. Also,
	 * a hypervisor might have set the individual AMD bits even on
	 * Intel CPUs, for finer-grained selection of what's available.
	 */
	if (cpu_has(c, X86_FEATURE_SPEC_CTRL)) {
		set_cpu_cap(c, X86_FEATURE_IBRS);
		set_cpu_cap(c, X86_FEATURE_IBPB);
		set_cpu_cap(c, X86_FEATURE_MSR_SPEC_CTRL);
	}

	if (cpu_has(c, X86_FEATURE_INTEL_STIBP))
		set_cpu_cap(c, X86_FEATURE_STIBP);

	if (cpu_has(c, X86_FEATURE_SPEC_CTRL_SSBD) ||
	    cpu_has(c, X86_FEATURE_VIRT_SSBD))
		set_cpu_cap(c, X86_FEATURE_SSBD);

	if (cpu_has(c, X86_FEATURE_AMD_IBRS)) {
		set_cpu_cap(c, X86_FEATURE_IBRS);
		set_cpu_cap(c, X86_FEATURE_MSR_SPEC_CTRL);
	}

	if (cpu_has(c, X86_FEATURE_AMD_IBPB))
		set_cpu_cap(c, X86_FEATURE_IBPB);

	if (cpu_has(c, X86_FEATURE_AMD_STIBP)) {
		set_cpu_cap(c, X86_FEATURE_STIBP);
		set_cpu_cap(c, X86_FEATURE_MSR_SPEC_CTRL);
	}

	if (cpu_has(c, X86_FEATURE_AMD_SSBD)) {
		set_cpu_cap(c, X86_FEATURE_SSBD);
		set_cpu_cap(c, X86_FEATURE_MSR_SPEC_CTRL);
		clear_cpu_cap(c, X86_FEATURE_VIRT_SSBD);
	}
}
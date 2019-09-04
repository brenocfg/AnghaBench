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
typedef  int /*<<< orphan*/  u64 ;
struct cpuinfo_x86 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_MISC_FEATURES_ENABLES ; 
 int /*<<< orphan*/  init_cpuid_fault (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  msr_misc_features_shadow ; 
 int /*<<< orphan*/  probe_xeon_phi_r3mwait (struct cpuinfo_x86*) ; 
 scalar_t__ rdmsrl_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_intel_misc_features(struct cpuinfo_x86 *c)
{
	u64 msr;

	if (rdmsrl_safe(MSR_MISC_FEATURES_ENABLES, &msr))
		return;

	/* Clear all MISC features */
	this_cpu_write(msr_misc_features_shadow, 0);

	/* Check features and update capabilities and shadow control bits */
	init_cpuid_fault(c);
	probe_xeon_phi_r3mwait(c);

	msr = this_cpu_read(msr_misc_features_shadow);
	wrmsrl(MSR_MISC_FEATURES_ENABLES, msr);
}
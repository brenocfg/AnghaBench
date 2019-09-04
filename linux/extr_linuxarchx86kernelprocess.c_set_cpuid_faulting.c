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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_MISC_FEATURES_ENABLES ; 
 int MSR_MISC_FEATURES_ENABLES_CPUID_FAULT ; 
 int MSR_MISC_FEATURES_ENABLES_CPUID_FAULT_BIT ; 
 int /*<<< orphan*/  msr_misc_features_shadow ; 
 int this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_cpuid_faulting(bool on)
{
	u64 msrval;

	msrval = this_cpu_read(msr_misc_features_shadow);
	msrval &= ~MSR_MISC_FEATURES_ENABLES_CPUID_FAULT;
	msrval |= (on << MSR_MISC_FEATURES_ENABLES_CPUID_FAULT_BIT);
	this_cpu_write(msr_misc_features_shadow, msrval);
	wrmsrl(MSR_MISC_FEATURES_ENABLES, msrval);
}
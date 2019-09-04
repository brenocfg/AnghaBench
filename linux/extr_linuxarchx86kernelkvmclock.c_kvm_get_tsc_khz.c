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
 int /*<<< orphan*/  X86_FEATURE_TSC_KNOWN_FREQ ; 
 unsigned long pvclock_tsc_khz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_force_cpu_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_pvti () ; 

__attribute__((used)) static unsigned long kvm_get_tsc_khz(void)
{
	setup_force_cpu_cap(X86_FEATURE_TSC_KNOWN_FREQ);
	return pvclock_tsc_khz(this_cpu_pvti());
}
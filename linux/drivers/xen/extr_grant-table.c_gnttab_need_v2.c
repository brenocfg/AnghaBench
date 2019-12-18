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
typedef  int uint32_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int XEN_CPUID_MACHINE_ADDRESS_WIDTH_MASK ; 
 int cpuid_eax (int) ; 
 int cpuid_ebx (int) ; 
 int max_possible_pfn ; 
 int xen_cpuid_base () ; 
 scalar_t__ xen_pv_domain () ; 

__attribute__((used)) static bool gnttab_need_v2(void)
{
#ifdef CONFIG_X86
	uint32_t base, width;

	if (xen_pv_domain()) {
		base = xen_cpuid_base();
		if (cpuid_eax(base) < 5)
			return false;	/* Information not available, use V1. */
		width = cpuid_ebx(base + 5) &
			XEN_CPUID_MACHINE_ADDRESS_WIDTH_MASK;
		return width > 32 + PAGE_SHIFT;
	}
#endif
	return !!(max_possible_pfn >> 32);
}
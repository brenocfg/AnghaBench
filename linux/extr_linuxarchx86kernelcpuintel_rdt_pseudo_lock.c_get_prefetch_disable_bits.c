#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_2__ {scalar_t__ x86_vendor; int x86; int x86_model; } ;

/* Variables and functions */
#define  INTEL_FAM6_ATOM_GEMINI_LAKE 130 
#define  INTEL_FAM6_ATOM_GOLDMONT 129 
#define  INTEL_FAM6_BROADWELL_X 128 
 scalar_t__ X86_VENDOR_INTEL ; 
 TYPE_1__ boot_cpu_data ; 

__attribute__((used)) static u64 get_prefetch_disable_bits(void)
{
	if (boot_cpu_data.x86_vendor != X86_VENDOR_INTEL ||
	    boot_cpu_data.x86 != 6)
		return 0;

	switch (boot_cpu_data.x86_model) {
	case INTEL_FAM6_BROADWELL_X:
		/*
		 * SDM defines bits of MSR_MISC_FEATURE_CONTROL register
		 * as:
		 * 0    L2 Hardware Prefetcher Disable (R/W)
		 * 1    L2 Adjacent Cache Line Prefetcher Disable (R/W)
		 * 2    DCU Hardware Prefetcher Disable (R/W)
		 * 3    DCU IP Prefetcher Disable (R/W)
		 * 63:4 Reserved
		 */
		return 0xF;
	case INTEL_FAM6_ATOM_GOLDMONT:
	case INTEL_FAM6_ATOM_GEMINI_LAKE:
		/*
		 * SDM defines bits of MSR_MISC_FEATURE_CONTROL register
		 * as:
		 * 0     L2 Hardware Prefetcher Disable (R/W)
		 * 1     Reserved
		 * 2     DCU Hardware Prefetcher Disable (R/W)
		 * 63:3  Reserved
		 */
		return 0x5;
	}

	return 0;
}
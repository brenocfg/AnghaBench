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
struct cpuinfo_x86 {int x86; int x86_model; int x86_cache_bits; } ;

/* Variables and functions */
#define  INTEL_FAM6_BROADWELL_CORE 140 
#define  INTEL_FAM6_BROADWELL_GT3E 139 
#define  INTEL_FAM6_HASWELL_CORE 138 
#define  INTEL_FAM6_HASWELL_GT3E 137 
#define  INTEL_FAM6_HASWELL_ULT 136 
#define  INTEL_FAM6_IVYBRIDGE 135 
#define  INTEL_FAM6_KABYLAKE_DESKTOP 134 
#define  INTEL_FAM6_KABYLAKE_MOBILE 133 
#define  INTEL_FAM6_NEHALEM 132 
#define  INTEL_FAM6_SANDYBRIDGE 131 
#define  INTEL_FAM6_SKYLAKE_DESKTOP 130 
#define  INTEL_FAM6_SKYLAKE_MOBILE 129 
#define  INTEL_FAM6_WESTMERE 128 

__attribute__((used)) static void override_cache_bits(struct cpuinfo_x86 *c)
{
	if (c->x86 != 6)
		return;

	switch (c->x86_model) {
	case INTEL_FAM6_NEHALEM:
	case INTEL_FAM6_WESTMERE:
	case INTEL_FAM6_SANDYBRIDGE:
	case INTEL_FAM6_IVYBRIDGE:
	case INTEL_FAM6_HASWELL_CORE:
	case INTEL_FAM6_HASWELL_ULT:
	case INTEL_FAM6_HASWELL_GT3E:
	case INTEL_FAM6_BROADWELL_CORE:
	case INTEL_FAM6_BROADWELL_GT3E:
	case INTEL_FAM6_SKYLAKE_MOBILE:
	case INTEL_FAM6_SKYLAKE_DESKTOP:
	case INTEL_FAM6_KABYLAKE_MOBILE:
	case INTEL_FAM6_KABYLAKE_DESKTOP:
		if (c->x86_cache_bits < 44)
			c->x86_cache_bits = 44;
		break;
	}
}
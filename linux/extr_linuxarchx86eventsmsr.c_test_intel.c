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
struct TYPE_2__ {scalar_t__ x86_vendor; int x86; int x86_model; } ;

/* Variables and functions */
#define  INTEL_FAM6_ATOM_AIRMONT 159 
#define  INTEL_FAM6_ATOM_DENVERTON 158 
#define  INTEL_FAM6_ATOM_GEMINI_LAKE 157 
#define  INTEL_FAM6_ATOM_GOLDMONT 156 
#define  INTEL_FAM6_ATOM_SILVERMONT1 155 
#define  INTEL_FAM6_ATOM_SILVERMONT2 154 
#define  INTEL_FAM6_BROADWELL_CORE 153 
#define  INTEL_FAM6_BROADWELL_GT3E 152 
#define  INTEL_FAM6_BROADWELL_X 151 
#define  INTEL_FAM6_BROADWELL_XEON_D 150 
#define  INTEL_FAM6_HASWELL_CORE 149 
#define  INTEL_FAM6_HASWELL_GT3E 148 
#define  INTEL_FAM6_HASWELL_ULT 147 
#define  INTEL_FAM6_HASWELL_X 146 
#define  INTEL_FAM6_IVYBRIDGE 145 
#define  INTEL_FAM6_IVYBRIDGE_X 144 
#define  INTEL_FAM6_KABYLAKE_DESKTOP 143 
#define  INTEL_FAM6_KABYLAKE_MOBILE 142 
#define  INTEL_FAM6_NEHALEM 141 
#define  INTEL_FAM6_NEHALEM_EP 140 
#define  INTEL_FAM6_NEHALEM_EX 139 
#define  INTEL_FAM6_NEHALEM_G 138 
#define  INTEL_FAM6_SANDYBRIDGE 137 
#define  INTEL_FAM6_SANDYBRIDGE_X 136 
#define  INTEL_FAM6_SKYLAKE_DESKTOP 135 
#define  INTEL_FAM6_SKYLAKE_MOBILE 134 
#define  INTEL_FAM6_SKYLAKE_X 133 
#define  INTEL_FAM6_WESTMERE 132 
#define  INTEL_FAM6_WESTMERE_EP 131 
#define  INTEL_FAM6_WESTMERE_EX 130 
#define  INTEL_FAM6_XEON_PHI_KNL 129 
#define  INTEL_FAM6_XEON_PHI_KNM 128 
 int PERF_MSR_PPERF ; 
 int PERF_MSR_SMI ; 
 scalar_t__ X86_VENDOR_INTEL ; 
 TYPE_1__ boot_cpu_data ; 

__attribute__((used)) static bool test_intel(int idx)
{
	if (boot_cpu_data.x86_vendor != X86_VENDOR_INTEL ||
	    boot_cpu_data.x86 != 6)
		return false;

	switch (boot_cpu_data.x86_model) {
	case INTEL_FAM6_NEHALEM:
	case INTEL_FAM6_NEHALEM_G:
	case INTEL_FAM6_NEHALEM_EP:
	case INTEL_FAM6_NEHALEM_EX:

	case INTEL_FAM6_WESTMERE:
	case INTEL_FAM6_WESTMERE_EP:
	case INTEL_FAM6_WESTMERE_EX:

	case INTEL_FAM6_SANDYBRIDGE:
	case INTEL_FAM6_SANDYBRIDGE_X:

	case INTEL_FAM6_IVYBRIDGE:
	case INTEL_FAM6_IVYBRIDGE_X:

	case INTEL_FAM6_HASWELL_CORE:
	case INTEL_FAM6_HASWELL_X:
	case INTEL_FAM6_HASWELL_ULT:
	case INTEL_FAM6_HASWELL_GT3E:

	case INTEL_FAM6_BROADWELL_CORE:
	case INTEL_FAM6_BROADWELL_XEON_D:
	case INTEL_FAM6_BROADWELL_GT3E:
	case INTEL_FAM6_BROADWELL_X:

	case INTEL_FAM6_ATOM_SILVERMONT1:
	case INTEL_FAM6_ATOM_SILVERMONT2:
	case INTEL_FAM6_ATOM_AIRMONT:

	case INTEL_FAM6_ATOM_GOLDMONT:
	case INTEL_FAM6_ATOM_DENVERTON:

	case INTEL_FAM6_ATOM_GEMINI_LAKE:

	case INTEL_FAM6_XEON_PHI_KNL:
	case INTEL_FAM6_XEON_PHI_KNM:
		if (idx == PERF_MSR_SMI)
			return true;
		break;

	case INTEL_FAM6_SKYLAKE_MOBILE:
	case INTEL_FAM6_SKYLAKE_DESKTOP:
	case INTEL_FAM6_SKYLAKE_X:
	case INTEL_FAM6_KABYLAKE_MOBILE:
	case INTEL_FAM6_KABYLAKE_DESKTOP:
		if (idx == PERF_MSR_SMI || idx == PERF_MSR_PPERF)
			return true;
		break;
	}

	return false;
}
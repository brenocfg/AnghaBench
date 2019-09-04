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
struct TYPE_2__ {scalar_t__ x86_vendor; int cpuid_level; int x86_model; } ;

/* Variables and functions */
#define  INTEL_FAM6_ATOM_DENVERTON 133 
#define  INTEL_FAM6_ATOM_GOLDMONT 132 
#define  INTEL_FAM6_KABYLAKE_DESKTOP 131 
#define  INTEL_FAM6_KABYLAKE_MOBILE 130 
#define  INTEL_FAM6_SKYLAKE_DESKTOP 129 
#define  INTEL_FAM6_SKYLAKE_MOBILE 128 
 int /*<<< orphan*/  X86_FEATURE_TSC_KNOWN_FREQ ; 
 int /*<<< orphan*/  X86_FEATURE_TSC_RELIABLE ; 
 scalar_t__ X86_VENDOR_INTEL ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  cpuid (int,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  setup_force_cpu_cap (int /*<<< orphan*/ ) ; 

unsigned long native_calibrate_tsc(void)
{
	unsigned int eax_denominator, ebx_numerator, ecx_hz, edx;
	unsigned int crystal_khz;

	if (boot_cpu_data.x86_vendor != X86_VENDOR_INTEL)
		return 0;

	if (boot_cpu_data.cpuid_level < 0x15)
		return 0;

	eax_denominator = ebx_numerator = ecx_hz = edx = 0;

	/* CPUID 15H TSC/Crystal ratio, plus optionally Crystal Hz */
	cpuid(0x15, &eax_denominator, &ebx_numerator, &ecx_hz, &edx);

	if (ebx_numerator == 0 || eax_denominator == 0)
		return 0;

	crystal_khz = ecx_hz / 1000;

	if (crystal_khz == 0) {
		switch (boot_cpu_data.x86_model) {
		case INTEL_FAM6_SKYLAKE_MOBILE:
		case INTEL_FAM6_SKYLAKE_DESKTOP:
		case INTEL_FAM6_KABYLAKE_MOBILE:
		case INTEL_FAM6_KABYLAKE_DESKTOP:
			crystal_khz = 24000;	/* 24.0 MHz */
			break;
		case INTEL_FAM6_ATOM_DENVERTON:
			crystal_khz = 25000;	/* 25.0 MHz */
			break;
		case INTEL_FAM6_ATOM_GOLDMONT:
			crystal_khz = 19200;	/* 19.2 MHz */
			break;
		}
	}

	if (crystal_khz == 0)
		return 0;
	/*
	 * TSC frequency determined by CPUID is a "hardware reported"
	 * frequency and is the most accurate one so far we have. This
	 * is considered a known frequency.
	 */
	setup_force_cpu_cap(X86_FEATURE_TSC_KNOWN_FREQ);

	/*
	 * For Atom SoCs TSC is the only reliable clocksource.
	 * Mark TSC reliable so no watchdog on it.
	 */
	if (boot_cpu_data.x86_model == INTEL_FAM6_ATOM_GOLDMONT)
		setup_force_cpu_cap(X86_FEATURE_TSC_RELIABLE);

	return crystal_khz * ebx_numerator / eax_denominator;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u64 ;
struct pvclock_vcpu_time_info {int flags; int tsc_shift; unsigned long long tsc_to_system_mul; int /*<<< orphan*/  tsc_timestamp; int /*<<< orphan*/  system_time; } ;
struct TYPE_3__ {int /*<<< orphan*/  tsc_scale; int /*<<< orphan*/  tsc_offset; } ;
typedef  TYPE_1__ HV_REFERENCE_TSC_PAGE ;

/* Variables and functions */
 int PVCLOCK_TSC_STABLE_BIT ; 
 int /*<<< orphan*/  do_div (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mul_u64_u32_div (unsigned long long,unsigned long long,int) ; 
 scalar_t__ mul_u64_u64_shr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool compute_tsc_page_parameters(struct pvclock_vcpu_time_info *hv_clock,
					HV_REFERENCE_TSC_PAGE *tsc_ref)
{
	u64 max_mul;

	if (!(hv_clock->flags & PVCLOCK_TSC_STABLE_BIT))
		return false;

	/*
	 * check if scale would overflow, if so we use the time ref counter
	 *    tsc_to_system_mul * 2^(tsc_shift+32) / 100 >= 2^64
	 *    tsc_to_system_mul / 100 >= 2^(32-tsc_shift)
	 *    tsc_to_system_mul >= 100 * 2^(32-tsc_shift)
	 */
	max_mul = 100ull << (32 - hv_clock->tsc_shift);
	if (hv_clock->tsc_to_system_mul >= max_mul)
		return false;

	/*
	 * Otherwise compute the scale and offset according to the formulas
	 * derived above.
	 */
	tsc_ref->tsc_scale =
		mul_u64_u32_div(1ULL << (32 + hv_clock->tsc_shift),
				hv_clock->tsc_to_system_mul,
				100);

	tsc_ref->tsc_offset = hv_clock->system_time;
	do_div(tsc_ref->tsc_offset, 100);
	tsc_ref->tsc_offset -=
		mul_u64_u64_shr(hv_clock->tsc_timestamp, tsc_ref->tsc_scale, 64);
	return true;
}
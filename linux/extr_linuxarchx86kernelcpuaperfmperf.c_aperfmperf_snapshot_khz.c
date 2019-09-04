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
typedef  scalar_t__ u64 ;
struct aperfmperf_sample {scalar_t__ aperf; scalar_t__ mperf; int /*<<< orphan*/  khz; int /*<<< orphan*/  time; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_APERF ; 
 int /*<<< orphan*/  MSR_IA32_MPERF ; 
 scalar_t__ cpu_khz ; 
 int /*<<< orphan*/  div64_u64 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  samples ; 
 struct aperfmperf_sample* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aperfmperf_snapshot_khz(void *dummy)
{
	u64 aperf, aperf_delta;
	u64 mperf, mperf_delta;
	struct aperfmperf_sample *s = this_cpu_ptr(&samples);
	unsigned long flags;

	local_irq_save(flags);
	rdmsrl(MSR_IA32_APERF, aperf);
	rdmsrl(MSR_IA32_MPERF, mperf);
	local_irq_restore(flags);

	aperf_delta = aperf - s->aperf;
	mperf_delta = mperf - s->mperf;

	/*
	 * There is no architectural guarantee that MPERF
	 * increments faster than we can read it.
	 */
	if (mperf_delta == 0)
		return;

	s->time = ktime_get();
	s->aperf = aperf;
	s->mperf = mperf;
	s->khz = div64_u64((cpu_khz * aperf_delta), mperf_delta);
}
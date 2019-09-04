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
struct hw_perf_event {int flags; size_t idx; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct intel_excl_states {int /*<<< orphan*/  sched_started; int /*<<< orphan*/ * state; } ;
struct intel_excl_cntrs {int /*<<< orphan*/  lock; struct intel_excl_states* states; int /*<<< orphan*/ * has_exclusive; } ;
struct cpu_hw_events {int excl_thread_id; int /*<<< orphan*/  n_excl; scalar_t__ is_fake; struct intel_excl_cntrs* excl_cntrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_EXCL_UNUSED ; 
 int PERF_X86_EVENT_EXCL_ACCT ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_put_excl_constraints(struct cpu_hw_events *cpuc,
		struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	struct intel_excl_cntrs *excl_cntrs = cpuc->excl_cntrs;
	int tid = cpuc->excl_thread_id;
	struct intel_excl_states *xl;

	/*
	 * nothing needed if in group validation mode
	 */
	if (cpuc->is_fake)
		return;

	if (WARN_ON_ONCE(!excl_cntrs))
		return;

	if (hwc->flags & PERF_X86_EVENT_EXCL_ACCT) {
		hwc->flags &= ~PERF_X86_EVENT_EXCL_ACCT;
		if (!--cpuc->n_excl)
			WRITE_ONCE(excl_cntrs->has_exclusive[tid], 0);
	}

	/*
	 * If event was actually assigned, then mark the counter state as
	 * unused now.
	 */
	if (hwc->idx >= 0) {
		xl = &excl_cntrs->states[tid];

		/*
		 * put_constraint may be called from x86_schedule_events()
		 * which already has the lock held so here make locking
		 * conditional.
		 */
		if (!xl->sched_started)
			raw_spin_lock(&excl_cntrs->lock);

		xl->state[hwc->idx] = INTEL_EXCL_UNUSED;

		if (!xl->sched_started)
			raw_spin_unlock(&excl_cntrs->lock);
	}
}
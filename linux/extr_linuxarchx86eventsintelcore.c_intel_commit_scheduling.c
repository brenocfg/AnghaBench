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
struct intel_excl_states {int /*<<< orphan*/ * state; } ;
struct intel_excl_cntrs {int /*<<< orphan*/  lock; struct intel_excl_states* states; } ;
struct event_constraint {int flags; } ;
struct cpu_hw_events {int excl_thread_id; scalar_t__ is_fake; struct event_constraint** event_constraint; struct intel_excl_cntrs* excl_cntrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_EXCL_EXCLUSIVE ; 
 int /*<<< orphan*/  INTEL_EXCL_SHARED ; 
 int PERF_X86_EVENT_DYNAMIC ; 
 int PERF_X86_EVENT_EXCL ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  is_ht_workaround_enabled () ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_commit_scheduling(struct cpu_hw_events *cpuc, int idx, int cntr)
{
	struct intel_excl_cntrs *excl_cntrs = cpuc->excl_cntrs;
	struct event_constraint *c = cpuc->event_constraint[idx];
	struct intel_excl_states *xl;
	int tid = cpuc->excl_thread_id;

	if (cpuc->is_fake || !is_ht_workaround_enabled())
		return;

	if (WARN_ON_ONCE(!excl_cntrs))
		return;

	if (!(c->flags & PERF_X86_EVENT_DYNAMIC))
		return;

	xl = &excl_cntrs->states[tid];

	lockdep_assert_held(&excl_cntrs->lock);

	if (c->flags & PERF_X86_EVENT_EXCL)
		xl->state[cntr] = INTEL_EXCL_EXCLUSIVE;
	else
		xl->state[cntr] = INTEL_EXCL_SHARED;
}
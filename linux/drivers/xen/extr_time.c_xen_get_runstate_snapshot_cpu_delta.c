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
typedef  int u64 ;
struct vcpu_runstate_info {int /*<<< orphan*/  state_entry_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 struct vcpu_runstate_info READ_ONCE (struct vcpu_runstate_info) ; 
 int XEN_RUNSTATE_UPDATE ; 
 int get64 (int /*<<< orphan*/ *) ; 
 struct vcpu_runstate_info* per_cpu_ptr (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  preemptible () ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  xen_runstate ; 

__attribute__((used)) static void xen_get_runstate_snapshot_cpu_delta(
			      struct vcpu_runstate_info *res, unsigned int cpu)
{
	u64 state_time;
	struct vcpu_runstate_info *state;

	BUG_ON(preemptible());

	state = per_cpu_ptr(&xen_runstate, cpu);

	do {
		state_time = get64(&state->state_entry_time);
		rmb();	/* Hypervisor might update data. */
		*res = READ_ONCE(*state);
		rmb();	/* Hypervisor might update data. */
	} while (get64(&state->state_entry_time) != state_time ||
		 (state_time & XEN_RUNSTATE_UPDATE));
}
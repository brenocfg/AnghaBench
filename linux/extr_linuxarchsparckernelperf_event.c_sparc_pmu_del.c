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
struct perf_event {int dummy; } ;
struct cpu_hw_events {int n_events; int /*<<< orphan*/ * current_idx; int /*<<< orphan*/ * events; struct perf_event** event; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EF_UPDATE ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  sparc_pmu_stop (struct perf_event*,int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sparc_pmu_del(struct perf_event *event, int _flags)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	unsigned long flags;
	int i;

	local_irq_save(flags);

	for (i = 0; i < cpuc->n_events; i++) {
		if (event == cpuc->event[i]) {
			/* Absorb the final count and turn off the
			 * event.
			 */
			sparc_pmu_stop(event, PERF_EF_UPDATE);

			/* Shift remaining entries down into
			 * the existing slot.
			 */
			while (++i < cpuc->n_events) {
				cpuc->event[i - 1] = cpuc->event[i];
				cpuc->events[i - 1] = cpuc->events[i];
				cpuc->current_idx[i - 1] =
					cpuc->current_idx[i];
			}

			perf_event_update_userpage(event);

			cpuc->n_events--;
			break;
		}
	}

	local_irq_restore(flags);
}
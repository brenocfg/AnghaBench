#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int state; } ;
struct perf_event {int /*<<< orphan*/  pmu; TYPE_3__ hw; } ;
struct TYPE_7__ {int h; unsigned long tear; unsigned long dear; int es; int ed; int /*<<< orphan*/  interval; scalar_t__ s; } ;
struct TYPE_6__ {scalar_t__ sdbt; } ;
struct cpu_hw_sf {int flags; struct perf_event* event; TYPE_2__ lsctl; int /*<<< orphan*/  handle; TYPE_1__ sfb; } ;
struct aux_buffer {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  PERF_EF_RELOAD ; 
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int PMU_F_IN_USE ; 
 scalar_t__ SAMPL_DIAG_MODE (TYPE_3__*) ; 
 int /*<<< orphan*/  SAMPL_RATE (TYPE_3__*) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int aux_output_begin (int /*<<< orphan*/ *,struct aux_buffer*,struct cpu_hw_sf*) ; 
 int /*<<< orphan*/  cpu_hw_sf ; 
 int /*<<< orphan*/  cpumsf_pmu_start (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_reset_registers (TYPE_3__*,scalar_t__) ; 
 struct aux_buffer* perf_aux_output_begin (int /*<<< orphan*/ *,struct perf_event*) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  perf_pmu_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_pmu_enable (int /*<<< orphan*/ ) ; 
 struct cpu_hw_sf* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpumsf_pmu_add(struct perf_event *event, int flags)
{
	struct cpu_hw_sf *cpuhw = this_cpu_ptr(&cpu_hw_sf);
	struct aux_buffer *aux;
	int err;

	if (cpuhw->flags & PMU_F_IN_USE)
		return -EAGAIN;

	if (!SAMPL_DIAG_MODE(&event->hw) && !cpuhw->sfb.sdbt)
		return -EINVAL;

	err = 0;
	perf_pmu_disable(event->pmu);

	event->hw.state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	/* Set up sampling controls.  Always program the sampling register
	 * using the SDB-table start.  Reset TEAR_REG event hardware register
	 * that is used by hw_perf_event_update() to store the sampling buffer
	 * position after samples have been flushed.
	 */
	cpuhw->lsctl.s = 0;
	cpuhw->lsctl.h = 1;
	cpuhw->lsctl.interval = SAMPL_RATE(&event->hw);
	if (!SAMPL_DIAG_MODE(&event->hw)) {
		cpuhw->lsctl.tear = (unsigned long) cpuhw->sfb.sdbt;
		cpuhw->lsctl.dear = *(unsigned long *) cpuhw->sfb.sdbt;
		hw_reset_registers(&event->hw, cpuhw->sfb.sdbt);
	}

	/* Ensure sampling functions are in the disabled state.  If disabled,
	 * switch on sampling enable control. */
	if (WARN_ON_ONCE(cpuhw->lsctl.es == 1 || cpuhw->lsctl.ed == 1)) {
		err = -EAGAIN;
		goto out;
	}
	if (SAMPL_DIAG_MODE(&event->hw)) {
		aux = perf_aux_output_begin(&cpuhw->handle, event);
		if (!aux) {
			err = -EINVAL;
			goto out;
		}
		err = aux_output_begin(&cpuhw->handle, aux, cpuhw);
		if (err)
			goto out;
		cpuhw->lsctl.ed = 1;
	}
	cpuhw->lsctl.es = 1;

	/* Set in_use flag and store event */
	cpuhw->event = event;
	cpuhw->flags |= PMU_F_IN_USE;

	if (flags & PERF_EF_START)
		cpumsf_pmu_start(event, PERF_EF_RELOAD);
out:
	perf_event_update_userpage(event);
	perf_pmu_enable(event->pmu);
	return err;
}
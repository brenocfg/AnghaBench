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
struct pt_regs {int dummy; } ;
struct perf_event {int dummy; } ;
struct cpu_hw_events {struct perf_event** event; } ;
struct TYPE_2__ {int n_counter; } ;

/* Variables and functions */
 int MSR_PMM ; 
 int PMGC0_FCECE ; 
 int PMGC0_PMIE ; 
 int /*<<< orphan*/  PMRN_PMGC0 ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 int /*<<< orphan*/  isync () ; 
 int mfmsr () ; 
 int /*<<< orphan*/  mtmsr (int) ; 
 int /*<<< orphan*/  mtpmr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nmi_enter () ; 
 int /*<<< orphan*/  nmi_exit () ; 
 int perf_intr_is_nmi (struct pt_regs*) ; 
 TYPE_1__* ppmu ; 
 unsigned long read_pmc (int) ; 
 int /*<<< orphan*/  record_and_restart (struct perf_event*,unsigned long,struct pt_regs*) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_pmc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void perf_event_interrupt(struct pt_regs *regs)
{
	int i;
	struct cpu_hw_events *cpuhw = this_cpu_ptr(&cpu_hw_events);
	struct perf_event *event;
	unsigned long val;
	int found = 0;
	int nmi;

	nmi = perf_intr_is_nmi(regs);
	if (nmi)
		nmi_enter();
	else
		irq_enter();

	for (i = 0; i < ppmu->n_counter; ++i) {
		event = cpuhw->event[i];

		val = read_pmc(i);
		if ((int)val < 0) {
			if (event) {
				/* event has overflowed */
				found = 1;
				record_and_restart(event, val, regs);
			} else {
				/*
				 * Disabled counter is negative,
				 * reset it just in case.
				 */
				write_pmc(i, 0);
			}
		}
	}

	/* PMM will keep counters frozen until we return from the interrupt. */
	mtmsr(mfmsr() | MSR_PMM);
	mtpmr(PMRN_PMGC0, PMGC0_PMIE | PMGC0_FCECE);
	isync();

	if (nmi)
		nmi_exit();
	else
		irq_exit();
}
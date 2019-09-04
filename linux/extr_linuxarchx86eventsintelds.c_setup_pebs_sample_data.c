#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct pt_regs {int flags; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  sp; int /*<<< orphan*/  bp; int /*<<< orphan*/  di; int /*<<< orphan*/  si; int /*<<< orphan*/  dx; int /*<<< orphan*/  cx; int /*<<< orphan*/  bx; int /*<<< orphan*/  ax; } ;
struct TYPE_7__ {int val; } ;
struct perf_sample_data {int /*<<< orphan*/ * br_stack; int /*<<< orphan*/  time; int /*<<< orphan*/  txn; int /*<<< orphan*/  weight; int /*<<< orphan*/  addr; int /*<<< orphan*/  callchain; TYPE_2__ data_src; int /*<<< orphan*/  period; } ;
struct TYPE_9__ {int sample_type; int precise_ip; scalar_t__ use_clockid; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  last_period; } ;
struct perf_event {TYPE_4__ attr; TYPE_1__ hw; } ;
struct pebs_record_skl {int flags; int /*<<< orphan*/  tsc; int /*<<< orphan*/  dla; int /*<<< orphan*/  ip; int /*<<< orphan*/  real_ip; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  sp; int /*<<< orphan*/  bp; int /*<<< orphan*/  di; int /*<<< orphan*/  si; int /*<<< orphan*/  dx; int /*<<< orphan*/  cx; int /*<<< orphan*/  bx; int /*<<< orphan*/  ax; int /*<<< orphan*/  dse; int /*<<< orphan*/  lat; } ;
struct cpu_hw_events {int /*<<< orphan*/  lbr_stack; } ;
struct TYPE_8__ {int pebs_format; } ;
struct TYPE_10__ {TYPE_3__ intel_cap; } ;

/* Variables and functions */
 int PERF_EFLAGS_EXACT ; 
 int PERF_MEM_NA ; 
 int PERF_SAMPLE_ADDR ; 
 int PERF_SAMPLE_CALLCHAIN ; 
 int PERF_SAMPLE_DATA_SRC ; 
 int PERF_SAMPLE_PHYS_ADDR ; 
 int PERF_SAMPLE_REGS_INTR ; 
 int PERF_SAMPLE_TRANSACTION ; 
 int PERF_SAMPLE_WEIGHT ; 
 int PERF_X86_EVENT_PEBS_LDLAT ; 
 int PERF_X86_EVENT_PEBS_LD_HSW ; 
 int PERF_X86_EVENT_PEBS_NA_HSW ; 
 int PERF_X86_EVENT_PEBS_ST ; 
 int PERF_X86_EVENT_PEBS_ST_HSW ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 scalar_t__ has_branch_stack (struct perf_event*) ; 
 int /*<<< orphan*/  intel_hsw_transaction (struct pebs_record_skl*) ; 
 int /*<<< orphan*/  intel_hsw_weight (struct pebs_record_skl*) ; 
 scalar_t__ intel_pmu_pebs_fixup_ip (struct pt_regs*) ; 
 int load_latency_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  native_sched_clock_from_tsc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_callchain (struct perf_event*,struct pt_regs*) ; 
 int /*<<< orphan*/  perf_sample_data_init (struct perf_sample_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int precise_datala_hsw (struct perf_event*,int /*<<< orphan*/ ) ; 
 int precise_store_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_linear_ip (struct pt_regs*,int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_5__ x86_pmu ; 

__attribute__((used)) static void setup_pebs_sample_data(struct perf_event *event,
				   struct pt_regs *iregs, void *__pebs,
				   struct perf_sample_data *data,
				   struct pt_regs *regs)
{
#define PERF_X86_EVENT_PEBS_HSW_PREC \
		(PERF_X86_EVENT_PEBS_ST_HSW | \
		 PERF_X86_EVENT_PEBS_LD_HSW | \
		 PERF_X86_EVENT_PEBS_NA_HSW)
	/*
	 * We cast to the biggest pebs_record but are careful not to
	 * unconditionally access the 'extra' entries.
	 */
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct pebs_record_skl *pebs = __pebs;
	u64 sample_type;
	int fll, fst, dsrc;
	int fl = event->hw.flags;

	if (pebs == NULL)
		return;

	sample_type = event->attr.sample_type;
	dsrc = sample_type & PERF_SAMPLE_DATA_SRC;

	fll = fl & PERF_X86_EVENT_PEBS_LDLAT;
	fst = fl & (PERF_X86_EVENT_PEBS_ST | PERF_X86_EVENT_PEBS_HSW_PREC);

	perf_sample_data_init(data, 0, event->hw.last_period);

	data->period = event->hw.last_period;

	/*
	 * Use latency for weight (only avail with PEBS-LL)
	 */
	if (fll && (sample_type & PERF_SAMPLE_WEIGHT))
		data->weight = pebs->lat;

	/*
	 * data.data_src encodes the data source
	 */
	if (dsrc) {
		u64 val = PERF_MEM_NA;
		if (fll)
			val = load_latency_data(pebs->dse);
		else if (fst && (fl & PERF_X86_EVENT_PEBS_HSW_PREC))
			val = precise_datala_hsw(event, pebs->dse);
		else if (fst)
			val = precise_store_data(pebs->dse);
		data->data_src.val = val;
	}

	/*
	 * We must however always use iregs for the unwinder to stay sane; the
	 * record BP,SP,IP can point into thin air when the record is from a
	 * previous PMI context or an (I)RET happend between the record and
	 * PMI.
	 */
	if (sample_type & PERF_SAMPLE_CALLCHAIN)
		data->callchain = perf_callchain(event, iregs);

	/*
	 * We use the interrupt regs as a base because the PEBS record does not
	 * contain a full regs set, specifically it seems to lack segment
	 * descriptors, which get used by things like user_mode().
	 *
	 * In the simple case fix up only the IP for PERF_SAMPLE_IP.
	 */
	*regs = *iregs;

	/*
	 * Initialize regs_>flags from PEBS,
	 * Clear exact bit (which uses x86 EFLAGS Reserved bit 3),
	 * i.e., do not rely on it being zero:
	 */
	regs->flags = pebs->flags & ~PERF_EFLAGS_EXACT;

	if (sample_type & PERF_SAMPLE_REGS_INTR) {
		regs->ax = pebs->ax;
		regs->bx = pebs->bx;
		regs->cx = pebs->cx;
		regs->dx = pebs->dx;
		regs->si = pebs->si;
		regs->di = pebs->di;

		regs->bp = pebs->bp;
		regs->sp = pebs->sp;

#ifndef CONFIG_X86_32
		regs->r8 = pebs->r8;
		regs->r9 = pebs->r9;
		regs->r10 = pebs->r10;
		regs->r11 = pebs->r11;
		regs->r12 = pebs->r12;
		regs->r13 = pebs->r13;
		regs->r14 = pebs->r14;
		regs->r15 = pebs->r15;
#endif
	}

	if (event->attr.precise_ip > 1) {
		/*
		 * Haswell and later processors have an 'eventing IP'
		 * (real IP) which fixes the off-by-1 skid in hardware.
		 * Use it when precise_ip >= 2 :
		 */
		if (x86_pmu.intel_cap.pebs_format >= 2) {
			set_linear_ip(regs, pebs->real_ip);
			regs->flags |= PERF_EFLAGS_EXACT;
		} else {
			/* Otherwise, use PEBS off-by-1 IP: */
			set_linear_ip(regs, pebs->ip);

			/*
			 * With precise_ip >= 2, try to fix up the off-by-1 IP
			 * using the LBR. If successful, the fixup function
			 * corrects regs->ip and calls set_linear_ip() on regs:
			 */
			if (intel_pmu_pebs_fixup_ip(regs))
				regs->flags |= PERF_EFLAGS_EXACT;
		}
	} else {
		/*
		 * When precise_ip == 1, return the PEBS off-by-1 IP,
		 * no fixup attempted:
		 */
		set_linear_ip(regs, pebs->ip);
	}


	if ((sample_type & (PERF_SAMPLE_ADDR | PERF_SAMPLE_PHYS_ADDR)) &&
	    x86_pmu.intel_cap.pebs_format >= 1)
		data->addr = pebs->dla;

	if (x86_pmu.intel_cap.pebs_format >= 2) {
		/* Only set the TSX weight when no memory weight. */
		if ((sample_type & PERF_SAMPLE_WEIGHT) && !fll)
			data->weight = intel_hsw_weight(pebs);

		if (sample_type & PERF_SAMPLE_TRANSACTION)
			data->txn = intel_hsw_transaction(pebs);
	}

	/*
	 * v3 supplies an accurate time stamp, so we use that
	 * for the time stamp.
	 *
	 * We can only do this for the default trace clock.
	 */
	if (x86_pmu.intel_cap.pebs_format >= 3 &&
		event->attr.use_clockid == 0)
		data->time = native_sched_clock_from_tsc(pebs->tsc);

	if (has_branch_stack(event))
		data->br_stack = &cpuc->lbr_stack;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct pt_regs {int dummy; } ;
struct perf_sample_data {int /*<<< orphan*/  addr; int /*<<< orphan*/  ip; } ;
struct perf_output_handle {int dummy; } ;
struct perf_event_header {int size; } ;
struct TYPE_5__ {int /*<<< orphan*/  interrupts; int /*<<< orphan*/  last_period; } ;
struct TYPE_4__ {scalar_t__ exclude_kernel; } ;
struct perf_event {int /*<<< orphan*/  pending_kill; TYPE_2__ hw; TYPE_1__ attr; } ;
struct debug_store {scalar_t__ bts_buffer_base; scalar_t__ bts_index; } ;
struct cpu_hw_events {struct perf_event** events; struct debug_store* ds; } ;
typedef  int /*<<< orphan*/  regs ;
struct TYPE_6__ {int /*<<< orphan*/  bts_active; } ;

/* Variables and functions */
 size_t INTEL_PMC_IDX_FIXED_BTS ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 scalar_t__ kernel_ip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ perf_output_begin (struct perf_output_handle*,struct perf_event*,int) ; 
 int /*<<< orphan*/  perf_output_end (struct perf_output_handle*) ; 
 int /*<<< orphan*/  perf_output_sample (struct perf_output_handle*,struct perf_event_header*,struct perf_sample_data*,struct perf_event*) ; 
 int /*<<< orphan*/  perf_prepare_sample (struct perf_event_header*,struct perf_sample_data*,struct perf_event*,struct pt_regs*) ; 
 int /*<<< orphan*/  perf_sample_data_init (struct perf_sample_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_3__ x86_pmu ; 

int intel_pmu_drain_bts_buffer(void)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct debug_store *ds = cpuc->ds;
	struct bts_record {
		u64	from;
		u64	to;
		u64	flags;
	};
	struct perf_event *event = cpuc->events[INTEL_PMC_IDX_FIXED_BTS];
	struct bts_record *at, *base, *top;
	struct perf_output_handle handle;
	struct perf_event_header header;
	struct perf_sample_data data;
	unsigned long skip = 0;
	struct pt_regs regs;

	if (!event)
		return 0;

	if (!x86_pmu.bts_active)
		return 0;

	base = (struct bts_record *)(unsigned long)ds->bts_buffer_base;
	top  = (struct bts_record *)(unsigned long)ds->bts_index;

	if (top <= base)
		return 0;

	memset(&regs, 0, sizeof(regs));

	ds->bts_index = ds->bts_buffer_base;

	perf_sample_data_init(&data, 0, event->hw.last_period);

	/*
	 * BTS leaks kernel addresses in branches across the cpl boundary,
	 * such as traps or system calls, so unless the user is asking for
	 * kernel tracing (and right now it's not possible), we'd need to
	 * filter them out. But first we need to count how many of those we
	 * have in the current batch. This is an extra O(n) pass, however,
	 * it's much faster than the other one especially considering that
	 * n <= 2560 (BTS_BUFFER_SIZE / BTS_RECORD_SIZE * 15/16; see the
	 * alloc_bts_buffer()).
	 */
	for (at = base; at < top; at++) {
		/*
		 * Note that right now *this* BTS code only works if
		 * attr::exclude_kernel is set, but let's keep this extra
		 * check here in case that changes.
		 */
		if (event->attr.exclude_kernel &&
		    (kernel_ip(at->from) || kernel_ip(at->to)))
			skip++;
	}

	/*
	 * Prepare a generic sample, i.e. fill in the invariant fields.
	 * We will overwrite the from and to address before we output
	 * the sample.
	 */
	rcu_read_lock();
	perf_prepare_sample(&header, &data, event, &regs);

	if (perf_output_begin(&handle, event, header.size *
			      (top - base - skip)))
		goto unlock;

	for (at = base; at < top; at++) {
		/* Filter out any records that contain kernel addresses. */
		if (event->attr.exclude_kernel &&
		    (kernel_ip(at->from) || kernel_ip(at->to)))
			continue;

		data.ip		= at->from;
		data.addr	= at->to;

		perf_output_sample(&handle, &header, &data, event);
	}

	perf_output_end(&handle);

	/* There's new data available. */
	event->hw.interrupts++;
	event->pending_kill = POLL_IN;
unlock:
	rcu_read_unlock();
	return 1;
}
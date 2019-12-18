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
typedef  int u64 ;
struct perf_output_handle {int /*<<< orphan*/  head; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct perf_event {TYPE_1__ hw; } ;
struct arm_spe_pmu_buf {scalar_t__ base; scalar_t__ snapshot; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERF_HES_STOPPED ; 
 int PERF_IDX2OFF (int /*<<< orphan*/ ,struct arm_spe_pmu_buf*) ; 
 int /*<<< orphan*/  SYS_PMBLIMITR_EL1 ; 
 int /*<<< orphan*/  SYS_PMBLIMITR_EL1_E_SHIFT ; 
 int /*<<< orphan*/  SYS_PMBPTR_EL1 ; 
 int arm_spe_pmu_next_off (struct perf_output_handle*) ; 
 int arm_spe_pmu_next_snapshot_off (struct perf_output_handle*) ; 
 struct arm_spe_pmu_buf* perf_aux_output_begin (struct perf_output_handle*,struct perf_event*) ; 
 int /*<<< orphan*/  write_sysreg_s (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arm_spe_perf_aux_output_begin(struct perf_output_handle *handle,
					  struct perf_event *event)
{
	u64 base, limit;
	struct arm_spe_pmu_buf *buf;

	/* Start a new aux session */
	buf = perf_aux_output_begin(handle, event);
	if (!buf) {
		event->hw.state |= PERF_HES_STOPPED;
		/*
		 * We still need to clear the limit pointer, since the
		 * profiler might only be disabled by virtue of a fault.
		 */
		limit = 0;
		goto out_write_limit;
	}

	limit = buf->snapshot ? arm_spe_pmu_next_snapshot_off(handle)
			      : arm_spe_pmu_next_off(handle);
	if (limit)
		limit |= BIT(SYS_PMBLIMITR_EL1_E_SHIFT);

	limit += (u64)buf->base;
	base = (u64)buf->base + PERF_IDX2OFF(handle->head, buf);
	write_sysreg_s(base, SYS_PMBPTR_EL1);

out_write_limit:
	write_sysreg_s(limit, SYS_PMBLIMITR_EL1);
}
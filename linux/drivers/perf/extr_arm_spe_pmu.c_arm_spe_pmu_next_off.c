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
typedef  scalar_t__ u64 ;
struct perf_output_handle {int /*<<< orphan*/  head; TYPE_1__* event; } ;
struct arm_spe_pmu_buf {int dummy; } ;
struct arm_spe_pmu {scalar_t__ max_record_sz; } ;
struct TYPE_2__ {int /*<<< orphan*/  pmu; } ;

/* Variables and functions */
 scalar_t__ PERF_IDX2OFF (int /*<<< orphan*/ ,struct arm_spe_pmu_buf*) ; 
 scalar_t__ __arm_spe_pmu_next_off (struct perf_output_handle*) ; 
 int /*<<< orphan*/  arm_spe_pmu_pad_buf (struct perf_output_handle*,scalar_t__) ; 
 struct arm_spe_pmu_buf* perf_get_aux (struct perf_output_handle*) ; 
 struct arm_spe_pmu* to_spe_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 arm_spe_pmu_next_off(struct perf_output_handle *handle)
{
	struct arm_spe_pmu_buf *buf = perf_get_aux(handle);
	struct arm_spe_pmu *spe_pmu = to_spe_pmu(handle->event->pmu);
	u64 limit = __arm_spe_pmu_next_off(handle);
	u64 head = PERF_IDX2OFF(handle->head, buf);

	/*
	 * If the head has come too close to the end of the buffer,
	 * then pad to the end and recompute the limit.
	 */
	if (limit && (limit - head < spe_pmu->max_record_sz)) {
		arm_spe_pmu_pad_buf(handle, limit - head);
		limit = __arm_spe_pmu_next_off(handle);
	}

	return limit;
}
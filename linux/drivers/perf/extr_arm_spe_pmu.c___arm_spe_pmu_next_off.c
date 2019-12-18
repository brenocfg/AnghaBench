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
typedef  unsigned long u64 ;
struct perf_output_handle {scalar_t__ head; unsigned long size; scalar_t__ wakeup; TYPE_1__* event; } ;
struct arm_spe_pmu_buf {unsigned long nr_pages; } ;
struct arm_spe_pmu {int /*<<< orphan*/  align; } ;
struct TYPE_2__ {int /*<<< orphan*/  pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  PERF_AUX_FLAG_TRUNCATED ; 
 unsigned long PERF_IDX2OFF (scalar_t__,struct arm_spe_pmu_buf*) ; 
 int /*<<< orphan*/  arm_spe_pmu_pad_buf (struct perf_output_handle*,unsigned long) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  perf_aux_output_end (struct perf_output_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_aux_output_flag (struct perf_output_handle*,int /*<<< orphan*/ ) ; 
 struct arm_spe_pmu_buf* perf_get_aux (struct perf_output_handle*) ; 
 unsigned long round_down (unsigned long,unsigned long) ; 
 unsigned long round_up (unsigned long,unsigned long) ; 
 unsigned long roundup (unsigned long,int /*<<< orphan*/ ) ; 
 struct arm_spe_pmu* to_spe_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 __arm_spe_pmu_next_off(struct perf_output_handle *handle)
{
	struct arm_spe_pmu *spe_pmu = to_spe_pmu(handle->event->pmu);
	struct arm_spe_pmu_buf *buf = perf_get_aux(handle);
	const u64 bufsize = buf->nr_pages * PAGE_SIZE;
	u64 limit = bufsize;
	u64 head, tail, wakeup;

	/*
	 * The head can be misaligned for two reasons:
	 *
	 * 1. The hardware left PMBPTR pointing to the first byte after
	 *    a record when generating a buffer management event.
	 *
	 * 2. We used perf_aux_output_skip to consume handle->size bytes
	 *    and CIRC_SPACE was used to compute the size, which always
	 *    leaves one entry free.
	 *
	 * Deal with this by padding to the next alignment boundary and
	 * moving the head index. If we run out of buffer space, we'll
	 * reduce handle->size to zero and end up reporting truncation.
	 */
	head = PERF_IDX2OFF(handle->head, buf);
	if (!IS_ALIGNED(head, spe_pmu->align)) {
		unsigned long delta = roundup(head, spe_pmu->align) - head;

		delta = min(delta, handle->size);
		arm_spe_pmu_pad_buf(handle, delta);
		head = PERF_IDX2OFF(handle->head, buf);
	}

	/* If we've run out of free space, then nothing more to do */
	if (!handle->size)
		goto no_space;

	/* Compute the tail and wakeup indices now that we've aligned head */
	tail = PERF_IDX2OFF(handle->head + handle->size, buf);
	wakeup = PERF_IDX2OFF(handle->wakeup, buf);

	/*
	 * Avoid clobbering unconsumed data. We know we have space, so
	 * if we see head == tail we know that the buffer is empty. If
	 * head > tail, then there's nothing to clobber prior to
	 * wrapping.
	 */
	if (head < tail)
		limit = round_down(tail, PAGE_SIZE);

	/*
	 * Wakeup may be arbitrarily far into the future. If it's not in
	 * the current generation, either we'll wrap before hitting it,
	 * or it's in the past and has been handled already.
	 *
	 * If there's a wakeup before we wrap, arrange to be woken up by
	 * the page boundary following it. Keep the tail boundary if
	 * that's lower.
	 */
	if (handle->wakeup < (handle->head + handle->size) && head <= wakeup)
		limit = min(limit, round_up(wakeup, PAGE_SIZE));

	if (limit > head)
		return limit;

	arm_spe_pmu_pad_buf(handle, handle->size);
no_space:
	perf_aux_output_flag(handle, PERF_AUX_FLAG_TRUNCATED);
	perf_aux_output_end(handle, 0);
	return 0;
}
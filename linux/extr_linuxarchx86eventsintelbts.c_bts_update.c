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
struct debug_store {unsigned long bts_index; unsigned long bts_buffer_base; scalar_t__ bts_absolute_maximum; } ;
struct bts_ctx {int /*<<< orphan*/  handle; } ;
struct bts_buffer {int /*<<< orphan*/  data_size; int /*<<< orphan*/  snapshot; int /*<<< orphan*/  head; int /*<<< orphan*/  cur_buf; } ;
struct TYPE_2__ {struct debug_store* ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_AUX_FLAG_TRUNCATED ; 
 unsigned long bts_buffer_offset (struct bts_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  local_add (unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_set (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long local_xchg (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__ per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perf_aux_output_flag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct bts_buffer* perf_get_aux (int /*<<< orphan*/ *) ; 
 int raw_smp_processor_id () ; 

__attribute__((used)) static void bts_update(struct bts_ctx *bts)
{
	int cpu = raw_smp_processor_id();
	struct debug_store *ds = per_cpu(cpu_hw_events, cpu).ds;
	struct bts_buffer *buf = perf_get_aux(&bts->handle);
	unsigned long index = ds->bts_index - ds->bts_buffer_base, old, head;

	if (!buf)
		return;

	head = index + bts_buffer_offset(buf, buf->cur_buf);
	old = local_xchg(&buf->head, head);

	if (!buf->snapshot) {
		if (old == head)
			return;

		if (ds->bts_index >= ds->bts_absolute_maximum)
			perf_aux_output_flag(&bts->handle,
			                     PERF_AUX_FLAG_TRUNCATED);

		/*
		 * old and head are always in the same physical buffer, so we
		 * can subtract them to get the data size.
		 */
		local_add(head - old, &buf->data_size);
	} else {
		local_set(&buf->data_size, head);
	}
}
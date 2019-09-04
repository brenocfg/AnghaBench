#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct perf_event {int dummy; } ;
struct debug_store {scalar_t__ bts_index; scalar_t__ bts_interrupt_threshold; } ;
struct TYPE_5__ {struct perf_event* event; } ;
struct bts_ctx {TYPE_1__ handle; int /*<<< orphan*/  state; struct debug_store* ds; } ;
struct bts_buffer {int /*<<< orphan*/  data_size; int /*<<< orphan*/  head; scalar_t__ snapshot; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 scalar_t__ BTS_STATE_STOPPED ; 
 int ENOSPC ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  barrier () ; 
 int bts_buffer_reset (struct bts_buffer*,TYPE_1__*) ; 
 int /*<<< orphan*/  bts_ctx ; 
 int /*<<< orphan*/  bts_update (struct bts_ctx*) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 scalar_t__ local_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct bts_buffer* perf_aux_output_begin (TYPE_1__*,struct perf_event*) ; 
 int /*<<< orphan*/  perf_aux_output_end (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct bts_buffer* perf_get_aux (TYPE_1__*) ; 
 struct bts_ctx* this_cpu_ptr (int /*<<< orphan*/ *) ; 

int intel_bts_interrupt(void)
{
	struct debug_store *ds = this_cpu_ptr(&cpu_hw_events)->ds;
	struct bts_ctx *bts = this_cpu_ptr(&bts_ctx);
	struct perf_event *event = bts->handle.event;
	struct bts_buffer *buf;
	s64 old_head;
	int err = -ENOSPC, handled = 0;

	/*
	 * The only surefire way of knowing if this NMI is ours is by checking
	 * the write ptr against the PMI threshold.
	 */
	if (ds && (ds->bts_index >= ds->bts_interrupt_threshold))
		handled = 1;

	/*
	 * this is wrapped in intel_bts_enable_local/intel_bts_disable_local,
	 * so we can only be INACTIVE or STOPPED
	 */
	if (READ_ONCE(bts->state) == BTS_STATE_STOPPED)
		return handled;

	buf = perf_get_aux(&bts->handle);
	if (!buf)
		return handled;

	/*
	 * Skip snapshot counters: they don't use the interrupt, but
	 * there's no other way of telling, because the pointer will
	 * keep moving
	 */
	if (buf->snapshot)
		return 0;

	old_head = local_read(&buf->head);
	bts_update(bts);

	/* no new data */
	if (old_head == local_read(&buf->head))
		return handled;

	perf_aux_output_end(&bts->handle, local_xchg(&buf->data_size, 0));

	buf = perf_aux_output_begin(&bts->handle, event);
	if (buf)
		err = bts_buffer_reset(buf, &bts->handle);

	if (err) {
		WRITE_ONCE(bts->state, BTS_STATE_STOPPED);

		if (buf) {
			/*
			 * BTS_STATE_STOPPED should be visible before
			 * cleared handle::event
			 */
			barrier();
			perf_aux_output_end(&bts->handle, 0);
		}
	}

	return 1;
}
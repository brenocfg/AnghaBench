#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pt_buffer {int nr_pages; int /*<<< orphan*/  data_size; scalar_t__ snapshot; } ;
struct TYPE_5__ {int /*<<< orphan*/  head; struct perf_event* event; } ;
struct pt {TYPE_2__ handle; int /*<<< orphan*/  handle_nmi; } ;
struct TYPE_4__ {scalar_t__ state; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int PERF_EF_UPDATE ; 
 scalar_t__ PERF_HES_STOPPED ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_xchg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  perf_aux_output_end (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct pt_buffer* perf_get_aux (TYPE_2__*) ; 
 int /*<<< orphan*/  pt_config_stop (struct perf_event*) ; 
 int /*<<< orphan*/  pt_ctx ; 
 int /*<<< orphan*/  pt_handle_status (struct pt*) ; 
 int /*<<< orphan*/  pt_read_offset (struct pt_buffer*) ; 
 int /*<<< orphan*/  pt_update_head (struct pt*) ; 
 struct pt* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pt_event_stop(struct perf_event *event, int mode)
{
	struct pt *pt = this_cpu_ptr(&pt_ctx);

	/*
	 * Protect against the PMI racing with disabling wrmsr,
	 * see comment in intel_pt_interrupt().
	 */
	WRITE_ONCE(pt->handle_nmi, 0);

	pt_config_stop(event);

	if (event->hw.state == PERF_HES_STOPPED)
		return;

	event->hw.state = PERF_HES_STOPPED;

	if (mode & PERF_EF_UPDATE) {
		struct pt_buffer *buf = perf_get_aux(&pt->handle);

		if (!buf)
			return;

		if (WARN_ON_ONCE(pt->handle.event != event))
			return;

		pt_read_offset(buf);

		pt_handle_status(pt);

		pt_update_head(pt);

		if (buf->snapshot)
			pt->handle.head =
				local_xchg(&buf->data_size,
					   buf->nr_pages << PAGE_SHIFT);
		perf_aux_output_end(&pt->handle, local_xchg(&buf->data_size, 0));
	}
}
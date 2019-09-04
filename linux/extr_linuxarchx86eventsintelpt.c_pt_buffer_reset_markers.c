#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_buffer {scalar_t__ output_off; size_t stop_pos; size_t intr_pos; int nr_pages; TYPE_1__** topa_index; int /*<<< orphan*/  cur_idx; int /*<<< orphan*/  cur; int /*<<< orphan*/  head; } ;
struct perf_output_handle {unsigned long size; unsigned long wakeup; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
struct TYPE_3__ {int stop; int intr; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PERF_AUX_FLAG_TRUNCATED ; 
 int /*<<< orphan*/  PT_CAP_topa_multiple_entries ; 
 TYPE_2__* TOPA_ENTRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long local64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  offset_in_page (unsigned long) ; 
 int /*<<< orphan*/  perf_aux_output_flag (struct perf_output_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_cap_get (int /*<<< orphan*/ ) ; 
 scalar_t__ sizes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pt_buffer_reset_markers(struct pt_buffer *buf,
				   struct perf_output_handle *handle)

{
	unsigned long head = local64_read(&buf->head);
	unsigned long idx, npages, wakeup;

	/* can't stop in the middle of an output region */
	if (buf->output_off + handle->size + 1 <
	    sizes(TOPA_ENTRY(buf->cur, buf->cur_idx)->size)) {
		perf_aux_output_flag(handle, PERF_AUX_FLAG_TRUNCATED);
		return -EINVAL;
	}


	/* single entry ToPA is handled by marking all regions STOP=1 INT=1 */
	if (!pt_cap_get(PT_CAP_topa_multiple_entries))
		return 0;

	/* clear STOP and INT from current entry */
	buf->topa_index[buf->stop_pos]->stop = 0;
	buf->topa_index[buf->stop_pos]->intr = 0;
	buf->topa_index[buf->intr_pos]->intr = 0;

	/* how many pages till the STOP marker */
	npages = handle->size >> PAGE_SHIFT;

	/* if it's on a page boundary, fill up one more page */
	if (!offset_in_page(head + handle->size + 1))
		npages++;

	idx = (head >> PAGE_SHIFT) + npages;
	idx &= buf->nr_pages - 1;
	buf->stop_pos = idx;

	wakeup = handle->wakeup >> PAGE_SHIFT;

	/* in the worst case, wake up the consumer one page before hard stop */
	idx = (head >> PAGE_SHIFT) + npages - 1;
	if (idx > wakeup)
		idx = wakeup;

	idx &= buf->nr_pages - 1;
	buf->intr_pos = idx;

	buf->topa_index[buf->stop_pos]->stop = 1;
	buf->topa_index[buf->stop_pos]->intr = 1;
	buf->topa_index[buf->intr_pos]->intr = 1;

	return 0;
}
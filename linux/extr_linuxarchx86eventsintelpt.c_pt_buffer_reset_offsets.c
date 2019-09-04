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
struct topa_entry {int dummy; } ;
struct topa {TYPE_1__* table; } ;
struct pt_buffer {int nr_pages; unsigned long cur_idx; unsigned long output_off; int /*<<< orphan*/  data_size; int /*<<< orphan*/  head; struct topa* cur; scalar_t__* topa_index; scalar_t__ snapshot; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  local_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pt_topa_next_entry (struct pt_buffer*,int) ; 
 int sizes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pt_buffer_reset_offsets(struct pt_buffer *buf, unsigned long head)
{
	int pg;

	if (buf->snapshot)
		head &= (buf->nr_pages << PAGE_SHIFT) - 1;

	pg = (head >> PAGE_SHIFT) & (buf->nr_pages - 1);
	pg = pt_topa_next_entry(buf, pg);

	buf->cur = (struct topa *)((unsigned long)buf->topa_index[pg] & PAGE_MASK);
	buf->cur_idx = ((unsigned long)buf->topa_index[pg] -
			(unsigned long)buf->cur) / sizeof(struct topa_entry);
	buf->output_off = head & (sizes(buf->cur->table[buf->cur_idx].size) - 1);

	local64_set(&buf->head, head);
	local_set(&buf->data_size, 0);
}
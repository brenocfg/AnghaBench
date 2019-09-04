#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dm_bufio_client {unsigned int block_size; } ;
struct dm_buffer {unsigned int dirty_start; unsigned int dirty_end; int /*<<< orphan*/  state; struct dm_bufio_client* c; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  B_DIRTY ; 
 int /*<<< orphan*/  B_READING ; 
 int /*<<< orphan*/  LIST_DIRTY ; 
 int /*<<< orphan*/  __relink_lru (struct dm_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_bufio_lock (struct dm_bufio_client*) ; 
 int /*<<< orphan*/  dm_bufio_unlock (struct dm_bufio_client*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void dm_bufio_mark_partial_buffer_dirty(struct dm_buffer *b,
					unsigned start, unsigned end)
{
	struct dm_bufio_client *c = b->c;

	BUG_ON(start >= end);
	BUG_ON(end > b->c->block_size);

	dm_bufio_lock(c);

	BUG_ON(test_bit(B_READING, &b->state));

	if (!test_and_set_bit(B_DIRTY, &b->state)) {
		b->dirty_start = start;
		b->dirty_end = end;
		__relink_lru(b, LIST_DIRTY);
	} else {
		if (start < b->dirty_start)
			b->dirty_start = start;
		if (end > b->dirty_end)
			b->dirty_end = end;
	}

	dm_bufio_unlock(c);
}
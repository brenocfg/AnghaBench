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
struct list_head {int dummy; } ;
struct dm_buffer {int /*<<< orphan*/  write_list; int /*<<< orphan*/  dirty_end; int /*<<< orphan*/  write_end; int /*<<< orphan*/  dirty_start; int /*<<< orphan*/  write_start; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_DIRTY ; 
 int /*<<< orphan*/  B_WRITING ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  submit_io (struct dm_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_bit_lock_io (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_endio ; 

__attribute__((used)) static void __write_dirty_buffer(struct dm_buffer *b,
				 struct list_head *write_list)
{
	if (!test_bit(B_DIRTY, &b->state))
		return;

	clear_bit(B_DIRTY, &b->state);
	wait_on_bit_lock_io(&b->state, B_WRITING, TASK_UNINTERRUPTIBLE);

	b->write_start = b->dirty_start;
	b->write_end = b->dirty_end;

	if (!write_list)
		submit_io(b, REQ_OP_WRITE, write_endio);
	else
		list_add_tail(&b->write_list, write_list);
}
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
struct dm_buffer {int /*<<< orphan*/  state; int /*<<< orphan*/  hold_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_READING ; 
 int /*<<< orphan*/  B_WRITING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __write_dirty_buffer (struct dm_buffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_bit_io (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __make_buffer_clean(struct dm_buffer *b)
{
	BUG_ON(b->hold_count);

	if (!b->state)	/* fast case */
		return;

	wait_on_bit_io(&b->state, B_READING, TASK_UNINTERRUPTIBLE);
	__write_dirty_buffer(b, NULL);
	wait_on_bit_io(&b->state, B_WRITING, TASK_UNINTERRUPTIBLE);
}
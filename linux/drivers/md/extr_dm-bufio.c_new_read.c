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
struct dm_bufio_client {int dummy; } ;
struct dm_buffer {int hold_count; void* data; scalar_t__ read_error; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  enum new_flag { ____Placeholder_new_flag } new_flag ;

/* Variables and functions */
 int /*<<< orphan*/  B_READING ; 
 void* ERR_PTR (int) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 struct dm_buffer* __bufio_new (struct dm_bufio_client*,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __flush_write_list (int /*<<< orphan*/ *) ; 
 int blk_status_to_errno (scalar_t__) ; 
 int /*<<< orphan*/  buffer_record_stack (struct dm_buffer*) ; 
 int /*<<< orphan*/  dm_bufio_lock (struct dm_bufio_client*) ; 
 int /*<<< orphan*/  dm_bufio_release (struct dm_buffer*) ; 
 int /*<<< orphan*/  dm_bufio_unlock (struct dm_bufio_client*) ; 
 int /*<<< orphan*/  read_endio ; 
 int /*<<< orphan*/  submit_io (struct dm_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_on_bit_io (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_list ; 

__attribute__((used)) static void *new_read(struct dm_bufio_client *c, sector_t block,
		      enum new_flag nf, struct dm_buffer **bp)
{
	int need_submit;
	struct dm_buffer *b;

	LIST_HEAD(write_list);

	dm_bufio_lock(c);
	b = __bufio_new(c, block, nf, &need_submit, &write_list);
#ifdef CONFIG_DM_DEBUG_BLOCK_STACK_TRACING
	if (b && b->hold_count == 1)
		buffer_record_stack(b);
#endif
	dm_bufio_unlock(c);

	__flush_write_list(&write_list);

	if (!b)
		return NULL;

	if (need_submit)
		submit_io(b, REQ_OP_READ, read_endio);

	wait_on_bit_io(&b->state, B_READING, TASK_UNINTERRUPTIBLE);

	if (b->read_error) {
		int error = blk_status_to_errno(b->read_error);

		dm_bufio_release(b);

		return ERR_PTR(error);
	}

	*bp = b;

	return b->data;
}
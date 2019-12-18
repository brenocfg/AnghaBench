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
struct dm_buffer {int dummy; } ;
struct blk_plug {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_PREFETCH ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 struct dm_buffer* __bufio_new (struct dm_bufio_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __flush_write_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dm_bufio_in_request () ; 
 int /*<<< orphan*/  dm_bufio_lock (struct dm_bufio_client*) ; 
 int /*<<< orphan*/  dm_bufio_release (struct dm_buffer*) ; 
 int /*<<< orphan*/  dm_bufio_unlock (struct dm_bufio_client*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_endio ; 
 int /*<<< orphan*/  submit_io (struct dm_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_list ; 

void dm_bufio_prefetch(struct dm_bufio_client *c,
		       sector_t block, unsigned n_blocks)
{
	struct blk_plug plug;

	LIST_HEAD(write_list);

	BUG_ON(dm_bufio_in_request());

	blk_start_plug(&plug);
	dm_bufio_lock(c);

	for (; n_blocks--; block++) {
		int need_submit;
		struct dm_buffer *b;
		b = __bufio_new(c, block, NF_PREFETCH, &need_submit,
				&write_list);
		if (unlikely(!list_empty(&write_list))) {
			dm_bufio_unlock(c);
			blk_finish_plug(&plug);
			__flush_write_list(&write_list);
			blk_start_plug(&plug);
			dm_bufio_lock(c);
		}
		if (unlikely(b != NULL)) {
			dm_bufio_unlock(c);

			if (need_submit)
				submit_io(b, REQ_OP_READ, read_endio);
			dm_bufio_release(b);

			cond_resched();

			if (!n_blocks)
				goto flush_plug;
			dm_bufio_lock(c);
		}
	}

	dm_bufio_unlock(c);

flush_plug:
	blk_finish_plug(&plug);
}
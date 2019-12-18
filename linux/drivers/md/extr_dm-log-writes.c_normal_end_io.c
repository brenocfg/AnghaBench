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
struct per_bio_data {struct pending_block* block; } ;
struct pending_block {int flags; int /*<<< orphan*/  list; } ;
struct log_writes_c {int /*<<< orphan*/  blocks_lock; int /*<<< orphan*/  unflushed_blocks; int /*<<< orphan*/  log_kthread; int /*<<< orphan*/  logging_blocks; } ;
struct dm_target {struct log_writes_c* private; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int DM_ENDIO_DONE ; 
 int LOG_FLUSH_FLAG ; 
 int LOG_FUA_FLAG ; 
 scalar_t__ WRITE ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 struct per_bio_data* dm_per_bio_data (struct bio*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int normal_end_io(struct dm_target *ti, struct bio *bio,
		blk_status_t *error)
{
	struct log_writes_c *lc = ti->private;
	struct per_bio_data *pb = dm_per_bio_data(bio, sizeof(struct per_bio_data));

	if (bio_data_dir(bio) == WRITE && pb->block) {
		struct pending_block *block = pb->block;
		unsigned long flags;

		spin_lock_irqsave(&lc->blocks_lock, flags);
		if (block->flags & LOG_FLUSH_FLAG) {
			list_splice_tail_init(&block->list, &lc->logging_blocks);
			list_add_tail(&block->list, &lc->logging_blocks);
			wake_up_process(lc->log_kthread);
		} else if (block->flags & LOG_FUA_FLAG) {
			list_add_tail(&block->list, &lc->logging_blocks);
			wake_up_process(lc->log_kthread);
		} else
			list_add_tail(&block->list, &lc->unflushed_blocks);
		spin_unlock_irqrestore(&lc->blocks_lock, flags);
	}

	return DM_ENDIO_DONE;
}
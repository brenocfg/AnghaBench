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
struct pending_block {int /*<<< orphan*/  list; int /*<<< orphan*/  flags; int /*<<< orphan*/  data; int /*<<< orphan*/  datalen; } ;
struct log_writes_c {int sectorsize; int /*<<< orphan*/  log_kthread; int /*<<< orphan*/  blocks_lock; int /*<<< orphan*/  logging_blocks; int /*<<< orphan*/  pending_blocks; } ;
struct log_write_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LOG_MARK_FLAG ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pending_block*) ; 
 int /*<<< orphan*/  kstrndup (char*,size_t,int /*<<< orphan*/ ) ; 
 struct pending_block* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int log_mark(struct log_writes_c *lc, char *data)
{
	struct pending_block *block;
	size_t maxsize = lc->sectorsize - sizeof(struct log_write_entry);

	block = kzalloc(sizeof(struct pending_block), GFP_KERNEL);
	if (!block) {
		DMERR("Error allocating pending block");
		return -ENOMEM;
	}

	block->data = kstrndup(data, maxsize - 1, GFP_KERNEL);
	if (!block->data) {
		DMERR("Error copying mark data");
		kfree(block);
		return -ENOMEM;
	}
	atomic_inc(&lc->pending_blocks);
	block->datalen = strlen(block->data);
	block->flags |= LOG_MARK_FLAG;
	spin_lock_irq(&lc->blocks_lock);
	list_add_tail(&block->list, &lc->logging_blocks);
	spin_unlock_irq(&lc->blocks_lock);
	wake_up_process(lc->log_kthread);
	return 0;
}
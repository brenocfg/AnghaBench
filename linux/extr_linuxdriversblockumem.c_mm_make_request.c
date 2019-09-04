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
struct request_queue {struct cardinfo* queuedata; } ;
struct cardinfo {int /*<<< orphan*/  lock; struct bio** biotail; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_size; scalar_t__ bi_sector; } ;
struct bio {int /*<<< orphan*/  bi_opf; struct bio* bi_next; TYPE_1__ bi_iter; } ;
typedef  int /*<<< orphan*/  blk_qc_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_QC_T_NONE ; 
 int /*<<< orphan*/  activate (struct cardinfo*) ; 
 int /*<<< orphan*/  blk_queue_split (struct request_queue*,struct bio**) ; 
 int /*<<< orphan*/  mm_check_plugged (struct cardinfo*) ; 
 scalar_t__ op_is_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static blk_qc_t mm_make_request(struct request_queue *q, struct bio *bio)
{
	struct cardinfo *card = q->queuedata;
	pr_debug("mm_make_request %llu %u\n",
		 (unsigned long long)bio->bi_iter.bi_sector,
		 bio->bi_iter.bi_size);

	blk_queue_split(q, &bio);

	spin_lock_irq(&card->lock);
	*card->biotail = bio;
	bio->bi_next = NULL;
	card->biotail = &bio->bi_next;
	if (op_is_sync(bio->bi_opf) || !mm_check_plugged(card))
		activate(card);
	spin_unlock_irq(&card->lock);

	return BLK_QC_T_NONE;
}
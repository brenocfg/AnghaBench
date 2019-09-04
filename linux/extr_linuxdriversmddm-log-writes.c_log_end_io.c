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
struct log_writes_c {int logging_enabled; int /*<<< orphan*/  blocks_lock; } ;
struct bio {scalar_t__ bi_status; struct log_writes_c* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  bio_free_pages (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  put_io_block (struct log_writes_c*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void log_end_io(struct bio *bio)
{
	struct log_writes_c *lc = bio->bi_private;

	if (bio->bi_status) {
		unsigned long flags;

		DMERR("Error writing log block, error=%d", bio->bi_status);
		spin_lock_irqsave(&lc->blocks_lock, flags);
		lc->logging_enabled = false;
		spin_unlock_irqrestore(&lc->blocks_lock, flags);
	}

	bio_free_pages(bio);
	put_io_block(lc);
	bio_put(bio);
}
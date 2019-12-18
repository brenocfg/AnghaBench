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
struct dm_integrity_io {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct dm_integrity_c {int /*<<< orphan*/  commit_work; int /*<<< orphan*/  commit_wq; TYPE_1__ endio_wait; int /*<<< orphan*/  flush_bio_list; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 struct bio* dm_bio_from_per_bio_data (struct dm_integrity_io*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void submit_flush_bio(struct dm_integrity_c *ic, struct dm_integrity_io *dio)
{
	struct bio *bio;
	unsigned long flags;

	spin_lock_irqsave(&ic->endio_wait.lock, flags);
	bio = dm_bio_from_per_bio_data(dio, sizeof(struct dm_integrity_io));
	bio_list_add(&ic->flush_bio_list, bio);
	spin_unlock_irqrestore(&ic->endio_wait.lock, flags);

	queue_work(ic->commit_wq, &ic->commit_work);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mapped_device {int /*<<< orphan*/  wait; int /*<<< orphan*/ * pending; int /*<<< orphan*/  stats; int /*<<< orphan*/  queue; } ;
struct dm_io {unsigned long start_time; int /*<<< orphan*/  stats_aux; struct bio* orig_bio; struct mapped_device* md; } ;
struct TYPE_4__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;
struct TYPE_5__ {int /*<<< orphan*/ * in_flight; } ;
struct TYPE_6__ {TYPE_2__ part0; } ;

/* Variables and functions */
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_op (struct bio*) ; 
 int /*<<< orphan*/  bio_sectors (struct bio*) ; 
 TYPE_3__* dm_disk (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_stats_account_io (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_stats_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generic_end_io_acct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,unsigned long) ; 
 unsigned long jiffies ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void end_io_acct(struct dm_io *io)
{
	struct mapped_device *md = io->md;
	struct bio *bio = io->orig_bio;
	unsigned long duration = jiffies - io->start_time;
	int pending;
	int rw = bio_data_dir(bio);

	generic_end_io_acct(md->queue, bio_op(bio), &dm_disk(md)->part0,
			    io->start_time);

	if (unlikely(dm_stats_used(&md->stats)))
		dm_stats_account_io(&md->stats, bio_data_dir(bio),
				    bio->bi_iter.bi_sector, bio_sectors(bio),
				    true, duration, &io->stats_aux);

	/*
	 * After this is decremented the bio must not be touched if it is
	 * a flush.
	 */
	pending = atomic_dec_return(&md->pending[rw]);
	atomic_set(&dm_disk(md)->part0.in_flight[rw], pending);
	pending += atomic_read(&md->pending[rw^0x1]);

	/* nudge anyone waiting on suspend queue */
	if (!pending)
		wake_up(&md->wait);
}
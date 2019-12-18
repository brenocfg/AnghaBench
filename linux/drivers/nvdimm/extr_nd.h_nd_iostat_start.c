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
struct gendisk {int /*<<< orphan*/  part0; int /*<<< orphan*/  queue; } ;
struct bio {struct gendisk* bi_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_op (struct bio*) ; 
 int /*<<< orphan*/  bio_sectors (struct bio*) ; 
 int /*<<< orphan*/  blk_queue_io_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_start_io_acct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 

__attribute__((used)) static inline bool nd_iostat_start(struct bio *bio, unsigned long *start)
{
	struct gendisk *disk = bio->bi_disk;

	if (!blk_queue_io_stat(disk->queue))
		return false;

	*start = jiffies;
	generic_start_io_acct(disk->queue, bio_op(bio), bio_sectors(bio),
			      &disk->part0);
	return true;
}
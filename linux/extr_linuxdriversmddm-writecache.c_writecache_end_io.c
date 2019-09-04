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
struct dm_writecache {int /*<<< orphan*/ * bio_in_progress_wait; int /*<<< orphan*/ * bio_in_progress; } ;
struct dm_target {struct dm_writecache* private; } ;
struct bio {int /*<<< orphan*/ * bi_private; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int bio_data_dir (struct bio*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int writecache_end_io(struct dm_target *ti, struct bio *bio, blk_status_t *status)
{
	struct dm_writecache *wc = ti->private;

	if (bio->bi_private != NULL) {
		int dir = bio_data_dir(bio);
		if (atomic_dec_and_test(&wc->bio_in_progress[dir]))
			if (unlikely(waitqueue_active(&wc->bio_in_progress_wait[dir])))
				wake_up(&wc->bio_in_progress_wait[dir]);
	}
	return 0;
}
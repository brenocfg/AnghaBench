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
struct mddev {int /*<<< orphan*/  flush_bio_pool; int /*<<< orphan*/  flush_pool; } ;
struct md_rdev {int dummy; } ;
struct flush_info {int /*<<< orphan*/  flush_work; int /*<<< orphan*/  flush_pending; struct mddev* mddev; struct bio* bio; struct flush_info* fi; struct md_rdev* rdev; } ;
struct flush_bio {int /*<<< orphan*/  flush_work; int /*<<< orphan*/  flush_pending; struct mddev* mddev; struct bio* bio; struct flush_bio* fi; struct md_rdev* rdev; } ;
struct TYPE_2__ {scalar_t__ bi_size; } ;
struct bio {TYPE_1__ bi_iter; struct flush_info* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  md_wq ; 
 int /*<<< orphan*/  mempool_free (struct flush_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,struct mddev*) ; 
 int /*<<< orphan*/  submit_flushes ; 

__attribute__((used)) static void md_end_flush(struct bio *fbio)
{
	struct flush_bio *fb = fbio->bi_private;
	struct md_rdev *rdev = fb->rdev;
	struct flush_info *fi = fb->fi;
	struct bio *bio = fi->bio;
	struct mddev *mddev = fi->mddev;

	rdev_dec_pending(rdev, mddev);

	if (atomic_dec_and_test(&fi->flush_pending)) {
		if (bio->bi_iter.bi_size == 0) {
			/* an empty barrier - all done */
			bio_endio(bio);
			mempool_free(fi, mddev->flush_pool);
		} else {
			INIT_WORK(&fi->flush_work, submit_flushes);
			queue_work(md_wq, &fi->flush_work);
		}
	}

	mempool_free(fb, mddev->flush_bio_pool);
	bio_put(fbio);
}
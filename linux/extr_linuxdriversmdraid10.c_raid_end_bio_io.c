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
struct r10conf {int dummy; } ;
struct r10bio {int /*<<< orphan*/  state; TYPE_1__* mddev; struct bio* master_bio; } ;
struct bio {int /*<<< orphan*/  bi_status; } ;
struct TYPE_2__ {struct r10conf* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  R10BIO_Uptodate ; 
 int /*<<< orphan*/  allow_barrier (struct r10conf*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  free_r10bio (struct r10bio*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raid_end_bio_io(struct r10bio *r10_bio)
{
	struct bio *bio = r10_bio->master_bio;
	struct r10conf *conf = r10_bio->mddev->private;

	if (!test_bit(R10BIO_Uptodate, &r10_bio->state))
		bio->bi_status = BLK_STS_IOERR;

	bio_endio(bio);
	/*
	 * Wake up any possible resync thread that waits for the device
	 * to go idle.
	 */
	allow_barrier(conf);

	free_r10bio(r10_bio);
}
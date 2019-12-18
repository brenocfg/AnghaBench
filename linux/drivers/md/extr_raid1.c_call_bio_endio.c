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
struct r1conf {int dummy; } ;
struct r1bio {int /*<<< orphan*/  sector; int /*<<< orphan*/  state; TYPE_1__* mddev; struct bio* master_bio; } ;
struct bio {int /*<<< orphan*/  bi_status; } ;
struct TYPE_2__ {struct r1conf* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  R1BIO_Uptodate ; 
 int /*<<< orphan*/  allow_barrier (struct r1conf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void call_bio_endio(struct r1bio *r1_bio)
{
	struct bio *bio = r1_bio->master_bio;
	struct r1conf *conf = r1_bio->mddev->private;

	if (!test_bit(R1BIO_Uptodate, &r1_bio->state))
		bio->bi_status = BLK_STS_IOERR;

	bio_endio(bio);
	/*
	 * Wake up any possible resync thread that waits for the device
	 * to go idle.
	 */
	allow_barrier(conf, r1_bio->sector);
}
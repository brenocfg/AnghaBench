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
struct r10bio {int /*<<< orphan*/  state; int /*<<< orphan*/ * master_bio; int /*<<< orphan*/  sectors; int /*<<< orphan*/  remaining; struct mddev* mddev; } ;
struct mddev {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  R10BIO_MadeGood ; 
 int /*<<< orphan*/  R10BIO_WriteError ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_done_sync (struct mddev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_buf (struct r10bio*) ; 
 int /*<<< orphan*/  reschedule_retry (struct r10bio*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void end_sync_request(struct r10bio *r10_bio)
{
	struct mddev *mddev = r10_bio->mddev;

	while (atomic_dec_and_test(&r10_bio->remaining)) {
		if (r10_bio->master_bio == NULL) {
			/* the primary of several recovery bios */
			sector_t s = r10_bio->sectors;
			if (test_bit(R10BIO_MadeGood, &r10_bio->state) ||
			    test_bit(R10BIO_WriteError, &r10_bio->state))
				reschedule_retry(r10_bio);
			else
				put_buf(r10_bio);
			md_done_sync(mddev, s, 1);
			break;
		} else {
			struct r10bio *r10_bio2 = (struct r10bio *)r10_bio->master_bio;
			if (test_bit(R10BIO_MadeGood, &r10_bio->state) ||
			    test_bit(R10BIO_WriteError, &r10_bio->state))
				reschedule_retry(r10_bio);
			else
				put_buf(r10_bio);
			r10_bio = r10_bio2;
		}
	}
}
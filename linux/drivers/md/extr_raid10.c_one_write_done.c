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
struct r10bio {int /*<<< orphan*/  state; int /*<<< orphan*/  remaining; } ;

/* Variables and functions */
 int /*<<< orphan*/  R10BIO_MadeGood ; 
 int /*<<< orphan*/  R10BIO_WriteError ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_write (struct r10bio*) ; 
 int /*<<< orphan*/  raid_end_bio_io (struct r10bio*) ; 
 int /*<<< orphan*/  reschedule_retry (struct r10bio*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void one_write_done(struct r10bio *r10_bio)
{
	if (atomic_dec_and_test(&r10_bio->remaining)) {
		if (test_bit(R10BIO_WriteError, &r10_bio->state))
			reschedule_retry(r10_bio);
		else {
			close_write(r10_bio);
			if (test_bit(R10BIO_MadeGood, &r10_bio->state))
				reschedule_retry(r10_bio);
			else
				raid_end_bio_io(r10_bio);
		}
	}
}
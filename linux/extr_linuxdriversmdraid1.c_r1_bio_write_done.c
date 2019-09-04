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
struct r1bio {int /*<<< orphan*/  state; int /*<<< orphan*/  remaining; } ;

/* Variables and functions */
 int /*<<< orphan*/  R1BIO_MadeGood ; 
 int /*<<< orphan*/  R1BIO_WriteError ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_write (struct r1bio*) ; 
 int /*<<< orphan*/  raid_end_bio_io (struct r1bio*) ; 
 int /*<<< orphan*/  reschedule_retry (struct r1bio*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r1_bio_write_done(struct r1bio *r1_bio)
{
	if (!atomic_dec_and_test(&r1_bio->remaining))
		return;

	if (test_bit(R1BIO_WriteError, &r1_bio->state))
		reschedule_retry(r1_bio);
	else {
		close_write(r1_bio);
		if (test_bit(R1BIO_MadeGood, &r1_bio->state))
			reschedule_retry(r1_bio);
		else
			raid_end_bio_io(r1_bio);
	}
}
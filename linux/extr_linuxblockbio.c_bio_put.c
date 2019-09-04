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
struct bio {int /*<<< orphan*/  __bi_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_BUG_ON (int) ; 
 int /*<<< orphan*/  BIO_REFFED ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_free (struct bio*) ; 

void bio_put(struct bio *bio)
{
	if (!bio_flagged(bio, BIO_REFFED))
		bio_free(bio);
	else {
		BIO_BUG_ON(!atomic_read(&bio->__bi_cnt));

		/*
		 * last put frees it
		 */
		if (atomic_dec_and_test(&bio->__bi_cnt))
			bio_free(bio);
	}
}
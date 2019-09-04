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
struct r1bio {int /*<<< orphan*/  state; struct bio* master_bio; } ;
struct TYPE_2__ {scalar_t__ bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  R1BIO_Returned ; 
 scalar_t__ WRITE ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 scalar_t__ bio_end_sector (struct bio*) ; 
 int /*<<< orphan*/  call_bio_endio (struct r1bio*) ; 
 int /*<<< orphan*/  free_r1bio (struct r1bio*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raid_end_bio_io(struct r1bio *r1_bio)
{
	struct bio *bio = r1_bio->master_bio;

	/* if nobody has done the final endio yet, do it now */
	if (!test_and_set_bit(R1BIO_Returned, &r1_bio->state)) {
		pr_debug("raid1: sync end %s on sectors %llu-%llu\n",
			 (bio_data_dir(bio) == WRITE) ? "write" : "read",
			 (unsigned long long) bio->bi_iter.bi_sector,
			 (unsigned long long) bio_end_sector(bio) - 1);

		call_bio_endio(r1_bio);
	}
	free_r1bio(r1_bio);
}
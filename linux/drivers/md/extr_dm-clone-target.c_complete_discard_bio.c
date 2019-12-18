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
struct clone {unsigned long region_shift; int /*<<< orphan*/  flags; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_CLONE_DISCARD_PASSDOWN ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_region_range (struct clone*,struct bio*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  remap_to_dest (struct clone*,struct bio*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trim_bio (struct bio*,unsigned long,unsigned long) ; 

__attribute__((used)) static void complete_discard_bio(struct clone *clone, struct bio *bio, bool success)
{
	unsigned long rs, re;

	/*
	 * If the destination device supports discards, remap and trim the
	 * discard bio and pass it down. Otherwise complete the bio
	 * immediately.
	 */
	if (test_bit(DM_CLONE_DISCARD_PASSDOWN, &clone->flags) && success) {
		remap_to_dest(clone, bio);
		bio_region_range(clone, bio, &rs, &re);
		trim_bio(bio, rs << clone->region_shift,
			 (re - rs) << clone->region_shift);
		generic_make_request(bio);
	} else
		bio_endio(bio);
}
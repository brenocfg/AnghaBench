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
struct dm_clone_region_hydration {TYPE_1__* clone; int /*<<< orphan*/  overwrite_bio_end_io; struct bio* overwrite_bio; } ;
struct bio {struct dm_clone_region_hydration* bi_private; int /*<<< orphan*/  bi_end_io; } ;
struct TYPE_2__ {int /*<<< orphan*/  hydrations_in_flight; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  overwrite_endio ; 

__attribute__((used)) static void hydration_overwrite(struct dm_clone_region_hydration *hd, struct bio *bio)
{
	/*
	 * We don't need to save and restore bio->bi_private because device
	 * mapper core generates a new bio for us to use, with clean
	 * bi_private.
	 */
	hd->overwrite_bio = bio;
	hd->overwrite_bio_end_io = bio->bi_end_io;

	bio->bi_end_io = overwrite_endio;
	bio->bi_private = hd;

	atomic_inc(&hd->clone->hydrations_in_flight);
	generic_make_request(bio);
}
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
struct dm_clone_region_hydration {int /*<<< orphan*/  status; int /*<<< orphan*/  overwrite_bio_end_io; } ;
struct bio {int /*<<< orphan*/  bi_status; int /*<<< orphan*/  bi_end_io; struct dm_clone_region_hydration* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  hydration_complete (struct dm_clone_region_hydration*) ; 

__attribute__((used)) static void overwrite_endio(struct bio *bio)
{
	struct dm_clone_region_hydration *hd = bio->bi_private;

	bio->bi_end_io = hd->overwrite_bio_end_io;
	hd->status = bio->bi_status;

	hydration_complete(hd);
}
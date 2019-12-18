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
struct dm_clone_region_hydration {scalar_t__ status; int /*<<< orphan*/  deferred_bios; scalar_t__ overwrite_bio; struct clone* clone; } ;
struct clone {int /*<<< orphan*/  hydrations_in_flight; } ;
typedef  scalar_t__ blk_status_t ;

/* Variables and functions */
 scalar_t__ BLK_STS_IOERR ; 
 scalar_t__ BLK_STS_OK ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  complete_overwrite_bio (struct clone*,scalar_t__) ; 
 int /*<<< orphan*/  fail_bios (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  free_hydration (struct dm_clone_region_hydration*) ; 
 int hydration_update_metadata (struct dm_clone_region_hydration*) ; 
 int /*<<< orphan*/  issue_deferred_bios (struct clone*,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  wakeup_hydration_waiters (struct clone*) ; 

__attribute__((used)) static void hydration_complete(struct dm_clone_region_hydration *hd)
{
	int r;
	blk_status_t status;
	struct clone *clone = hd->clone;

	r = hydration_update_metadata(hd);

	if (hd->status == BLK_STS_OK && likely(!r)) {
		if (hd->overwrite_bio)
			complete_overwrite_bio(clone, hd->overwrite_bio);

		issue_deferred_bios(clone, &hd->deferred_bios);
	} else {
		status = r ? BLK_STS_IOERR : hd->status;

		if (hd->overwrite_bio)
			bio_list_add(&hd->deferred_bios, hd->overwrite_bio);

		fail_bios(&hd->deferred_bios, status);
	}

	free_hydration(hd);

	if (atomic_dec_and_test(&clone->hydrations_in_flight))
		wakeup_hydration_waiters(clone);
}
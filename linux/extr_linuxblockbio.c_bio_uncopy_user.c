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
struct bio_map_data {scalar_t__ is_our_pages; int /*<<< orphan*/  iter; } ;
struct bio {struct bio_map_data* bi_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_NULL_MAPPED ; 
 int EINTR ; 
 scalar_t__ READ ; 
 int bio_copy_to_iter (struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_free_pages (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  kfree (struct bio_map_data*) ; 

int bio_uncopy_user(struct bio *bio)
{
	struct bio_map_data *bmd = bio->bi_private;
	int ret = 0;

	if (!bio_flagged(bio, BIO_NULL_MAPPED)) {
		/*
		 * if we're in a workqueue, the request is orphaned, so
		 * don't copy into a random user address space, just free
		 * and return -EINTR so user space doesn't expect any data.
		 */
		if (!current->mm)
			ret = -EINTR;
		else if (bio_data_dir(bio) == READ)
			ret = bio_copy_to_iter(bio, bmd->iter);
		if (bmd->is_our_pages)
			bio_free_pages(bio);
	}
	kfree(bmd);
	bio_put(bio);
	return ret;
}
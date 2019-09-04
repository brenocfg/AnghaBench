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
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 struct bio* bio_alloc_bioset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioset_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drbd_md_io_bio_set ; 

struct bio *bio_alloc_drbd(gfp_t gfp_mask)
{
	struct bio *bio;

	if (!bioset_initialized(&drbd_md_io_bio_set))
		return bio_alloc(gfp_mask, 1);

	bio = bio_alloc_bioset(gfp_mask, 1, &drbd_md_io_bio_set);
	if (!bio)
		return NULL;
	return bio;
}
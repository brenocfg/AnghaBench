#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; scalar_t__ sector; int offset; } ;
struct md_rdev {scalar_t__ data_offset; scalar_t__ sectors; int sb_size; TYPE_1__ ppl; int /*<<< orphan*/  bdev; TYPE_2__* mddev; } ;
struct TYPE_4__ {int /*<<< orphan*/  external; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int EINVAL ; 
 int ENOSPC ; 
 int PPL_HEADER_SIZE ; 
 int /*<<< orphan*/  STRIPE_SECTORS ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdname (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rounddown (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ppl_validate_rdev(struct md_rdev *rdev)
{
	char b[BDEVNAME_SIZE];
	int ppl_data_sectors;
	int ppl_size_new;

	/*
	 * The configured PPL size must be enough to store
	 * the header and (at the very least) partial parity
	 * for one stripe. Round it down to ensure the data
	 * space is cleanly divisible by stripe size.
	 */
	ppl_data_sectors = rdev->ppl.size - (PPL_HEADER_SIZE >> 9);

	if (ppl_data_sectors > 0)
		ppl_data_sectors = rounddown(ppl_data_sectors, STRIPE_SECTORS);

	if (ppl_data_sectors <= 0) {
		pr_warn("md/raid:%s: PPL space too small on %s\n",
			mdname(rdev->mddev), bdevname(rdev->bdev, b));
		return -ENOSPC;
	}

	ppl_size_new = ppl_data_sectors + (PPL_HEADER_SIZE >> 9);

	if ((rdev->ppl.sector < rdev->data_offset &&
	     rdev->ppl.sector + ppl_size_new > rdev->data_offset) ||
	    (rdev->ppl.sector >= rdev->data_offset &&
	     rdev->data_offset + rdev->sectors > rdev->ppl.sector)) {
		pr_warn("md/raid:%s: PPL space overlaps with data on %s\n",
			mdname(rdev->mddev), bdevname(rdev->bdev, b));
		return -EINVAL;
	}

	if (!rdev->mddev->external &&
	    ((rdev->ppl.offset > 0 && rdev->ppl.offset < (rdev->sb_size >> 9)) ||
	     (rdev->ppl.offset <= 0 && rdev->ppl.offset + ppl_size_new > 0))) {
		pr_warn("md/raid:%s: PPL space overlaps with superblock on %s\n",
			mdname(rdev->mddev), bdevname(rdev->bdev, b));
		return -EINVAL;
	}

	rdev->ppl.size = ppl_size_new;

	return 0;
}
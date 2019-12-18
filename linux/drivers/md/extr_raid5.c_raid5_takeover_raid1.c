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
struct mddev {int raid_disks; int degraded; int array_sectors; int new_level; int new_chunk_sectors; int /*<<< orphan*/  new_layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALGORITHM_LEFT_SYMMETRIC ; 
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (void*) ; 
 int STRIPE_SIZE ; 
 int /*<<< orphan*/  UNSUPPORTED_MDDEV_FLAGS ; 
 int /*<<< orphan*/  mddev_clear_unsupported_flags (struct mddev*,int /*<<< orphan*/ ) ; 
 void* setup_conf (struct mddev*) ; 

__attribute__((used)) static void *raid5_takeover_raid1(struct mddev *mddev)
{
	int chunksect;
	void *ret;

	if (mddev->raid_disks != 2 ||
	    mddev->degraded > 1)
		return ERR_PTR(-EINVAL);

	/* Should check if there are write-behind devices? */

	chunksect = 64*2; /* 64K by default */

	/* The array must be an exact multiple of chunksize */
	while (chunksect && (mddev->array_sectors & (chunksect-1)))
		chunksect >>= 1;

	if ((chunksect<<9) < STRIPE_SIZE)
		/* array size does not allow a suitable chunk size */
		return ERR_PTR(-EINVAL);

	mddev->new_level = 5;
	mddev->new_layout = ALGORITHM_LEFT_SYMMETRIC;
	mddev->new_chunk_sectors = chunksect;

	ret = setup_conf(mddev);
	if (!IS_ERR(ret))
		mddev_clear_unsupported_flags(mddev,
			UNSUPPORTED_MDDEV_FLAGS);
	return ret;
}
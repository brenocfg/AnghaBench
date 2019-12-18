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
struct mddev {int /*<<< orphan*/  gendisk; } ;
struct md_rdev {TYPE_1__* bdev; } ;
struct blk_integrity {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bd_disk; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int ENXIO ; 
 int /*<<< orphan*/  bdevname (TYPE_1__*,char*) ; 
 struct blk_integrity* blk_get_integrity (int /*<<< orphan*/ ) ; 
 scalar_t__ blk_integrity_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int md_integrity_add_rdev(struct md_rdev *rdev, struct mddev *mddev)
{
	struct blk_integrity *bi_mddev;
	char name[BDEVNAME_SIZE];

	if (!mddev->gendisk)
		return 0;

	bi_mddev = blk_get_integrity(mddev->gendisk);

	if (!bi_mddev) /* nothing to do */
		return 0;

	if (blk_integrity_compare(mddev->gendisk, rdev->bdev->bd_disk) != 0) {
		pr_err("%s: incompatible integrity profile for %s\n",
		       mdname(mddev), bdevname(rdev->bdev, name));
		return -ENXIO;
	}

	return 0;
}
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
struct mddev {scalar_t__ array_sectors; int external_size; int /*<<< orphan*/  gendisk; TYPE_1__* pers; } ;
typedef  int ssize_t ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {scalar_t__ (* size ) (struct mddev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 scalar_t__ mddev_is_clustered (struct mddev*) ; 
 int mddev_lock (struct mddev*) ; 
 int /*<<< orphan*/  mddev_unlock (struct mddev*) ; 
 int /*<<< orphan*/  revalidate_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_capacity (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strict_blocks_to_sectors (char const*,scalar_t__*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 scalar_t__ stub1 (struct mddev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct mddev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
array_size_store(struct mddev *mddev, const char *buf, size_t len)
{
	sector_t sectors;
	int err;

	err = mddev_lock(mddev);
	if (err)
		return err;

	/* cluster raid doesn't support change array_sectors */
	if (mddev_is_clustered(mddev)) {
		mddev_unlock(mddev);
		return -EINVAL;
	}

	if (strncmp(buf, "default", 7) == 0) {
		if (mddev->pers)
			sectors = mddev->pers->size(mddev, 0, 0);
		else
			sectors = mddev->array_sectors;

		mddev->external_size = 0;
	} else {
		if (strict_blocks_to_sectors(buf, &sectors) < 0)
			err = -EINVAL;
		else if (mddev->pers && mddev->pers->size(mddev, 0, 0) < sectors)
			err = -E2BIG;
		else
			mddev->external_size = 1;
	}

	if (!err) {
		mddev->array_sectors = sectors;
		if (mddev->pers) {
			set_capacity(mddev->gendisk, mddev->array_sectors);
			revalidate_disk(mddev->gendisk);
		}
	}
	mddev_unlock(mddev);
	return err ?: len;
}
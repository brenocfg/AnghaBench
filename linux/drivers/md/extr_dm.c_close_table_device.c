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
struct TYPE_2__ {int mode; int /*<<< orphan*/ * dax_dev; int /*<<< orphan*/ * bdev; } ;
struct table_device {TYPE_1__ dm_dev; } ;
struct mapped_device {int dummy; } ;

/* Variables and functions */
 int FMODE_EXCL ; 
 int /*<<< orphan*/  bd_unlink_disk_holder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkdev_put (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dm_disk (struct mapped_device*) ; 
 int /*<<< orphan*/  put_dax (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_table_device(struct table_device *td, struct mapped_device *md)
{
	if (!td->dm_dev.bdev)
		return;

	bd_unlink_disk_holder(td->dm_dev.bdev, dm_disk(md));
	blkdev_put(td->dm_dev.bdev, td->dm_dev.mode | FMODE_EXCL);
	put_dax(td->dm_dev.dax_dev);
	td->dm_dev.bdev = NULL;
	td->dm_dev.dax_dev = NULL;
}
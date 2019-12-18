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
struct mapped_device {int dummy; } ;
struct dm_dev_internal {struct dm_dev* dm_dev; } ;
struct dm_dev {int mode; TYPE_1__* bdev; } ;
typedef  int fmode_t ;
struct TYPE_2__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int dm_get_table_device (struct mapped_device*,int /*<<< orphan*/ ,int,struct dm_dev**) ; 
 int /*<<< orphan*/  dm_put_table_device (struct mapped_device*,struct dm_dev*) ; 

__attribute__((used)) static int upgrade_mode(struct dm_dev_internal *dd, fmode_t new_mode,
			struct mapped_device *md)
{
	int r;
	struct dm_dev *old_dev, *new_dev;

	old_dev = dd->dm_dev;

	r = dm_get_table_device(md, dd->dm_dev->bdev->bd_dev,
				dd->dm_dev->mode | new_mode, &new_dev);
	if (r)
		return r;

	dd->dm_dev = new_dev;
	dm_put_table_device(md, old_dev);

	return 0;
}
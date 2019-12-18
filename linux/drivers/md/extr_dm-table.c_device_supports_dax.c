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
struct dm_target {int dummy; } ;
struct dm_dev {int /*<<< orphan*/  bdev; int /*<<< orphan*/  dax_dev; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int generic_fsdax_supported (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int device_supports_dax(struct dm_target *ti, struct dm_dev *dev,
			sector_t start, sector_t len, void *data)
{
	int blocksize = *(int *) data;

	return generic_fsdax_supported(dev->dax_dev, dev->bdev, blocksize,
				       start, len);
}
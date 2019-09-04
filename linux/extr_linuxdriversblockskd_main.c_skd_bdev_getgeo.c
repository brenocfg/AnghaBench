#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct skd_device {int /*<<< orphan*/  disk; scalar_t__ read_cap_is_valid; TYPE_2__* pdev; } ;
struct hd_geometry {int heads; int sectors; int cylinders; } ;
struct block_device {TYPE_1__* bd_disk; } ;
struct TYPE_6__ {int /*<<< orphan*/  comm; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  disk_name; struct skd_device* private_data; } ;

/* Variables and functions */
 int EIO ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_capacity (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skd_bdev_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	struct skd_device *skdev;
	u64 capacity;

	skdev = bdev->bd_disk->private_data;

	dev_dbg(&skdev->pdev->dev, "%s: CMD[%s] getgeo device\n",
		bdev->bd_disk->disk_name, current->comm);

	if (skdev->read_cap_is_valid) {
		capacity = get_capacity(skdev->disk);
		geo->heads = 64;
		geo->sectors = 255;
		geo->cylinders = (capacity) / (255 * 64);

		return 0;
	}
	return -EIO;
}
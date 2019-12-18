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
struct mspro_block_data {scalar_t__ read_only; int /*<<< orphan*/  usage_count; scalar_t__ card; } ;
struct gendisk {struct mspro_block_data* private_data; } ;
struct block_device {struct gendisk* bd_disk; } ;
typedef  int fmode_t ;

/* Variables and functions */
 int ENXIO ; 
 int EROFS ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  mspro_block_disk_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mspro_block_bd_open(struct block_device *bdev, fmode_t mode)
{
	struct gendisk *disk = bdev->bd_disk;
	struct mspro_block_data *msb = disk->private_data;
	int rc = -ENXIO;

	mutex_lock(&mspro_block_disk_lock);

	if (msb && msb->card) {
		msb->usage_count++;
		if ((mode & FMODE_WRITE) && msb->read_only)
			rc = -EROFS;
		else
			rc = 0;
	}

	mutex_unlock(&mspro_block_disk_lock);

	return rc;
}
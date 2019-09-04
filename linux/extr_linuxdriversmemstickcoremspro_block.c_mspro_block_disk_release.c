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
struct mspro_block_data {scalar_t__ usage_count; } ;
struct gendisk {struct mspro_block_data* private_data; } ;

/* Variables and functions */
 int MINOR (int /*<<< orphan*/ ) ; 
 int MSPRO_BLOCK_PART_SHIFT ; 
 int /*<<< orphan*/  disk_devt (struct gendisk*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct mspro_block_data*) ; 
 int /*<<< orphan*/  mspro_block_disk_idr ; 
 int /*<<< orphan*/  mspro_block_disk_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 

__attribute__((used)) static void mspro_block_disk_release(struct gendisk *disk)
{
	struct mspro_block_data *msb = disk->private_data;
	int disk_id = MINOR(disk_devt(disk)) >> MSPRO_BLOCK_PART_SHIFT;

	mutex_lock(&mspro_block_disk_lock);

	if (msb) {
		if (msb->usage_count)
			msb->usage_count--;

		if (!msb->usage_count) {
			kfree(msb);
			disk->private_data = NULL;
			idr_remove(&mspro_block_disk_idr, disk_id);
			put_disk(disk);
		}
	}

	mutex_unlock(&mspro_block_disk_lock);
}
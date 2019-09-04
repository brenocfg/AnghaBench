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
struct msb_data {int /*<<< orphan*/  usage_count; scalar_t__ card; } ;
struct gendisk {struct msb_data* private_data; } ;
struct block_device {struct gendisk* bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_verbose (char*) ; 
 int /*<<< orphan*/  msb_disk_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msb_bd_open(struct block_device *bdev, fmode_t mode)
{
	struct gendisk *disk = bdev->bd_disk;
	struct msb_data *msb = disk->private_data;

	dbg_verbose("block device open");

	mutex_lock(&msb_disk_lock);

	if (msb && msb->card)
		msb->usage_count++;

	mutex_unlock(&msb_disk_lock);
	return 0;
}
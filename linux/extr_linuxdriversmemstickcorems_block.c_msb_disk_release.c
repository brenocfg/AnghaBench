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
struct msb_data {int /*<<< orphan*/  disk_id; scalar_t__ usage_count; } ;
struct gendisk {struct msb_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_verbose (char*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct msb_data*) ; 
 int /*<<< orphan*/  msb_disk_idr ; 
 int /*<<< orphan*/  msb_disk_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 

__attribute__((used)) static int msb_disk_release(struct gendisk *disk)
{
	struct msb_data *msb = disk->private_data;

	dbg_verbose("block device release");
	mutex_lock(&msb_disk_lock);

	if (msb) {
		if (msb->usage_count)
			msb->usage_count--;

		if (!msb->usage_count) {
			disk->private_data = NULL;
			idr_remove(&msb_disk_idr, msb->disk_id);
			put_disk(disk);
			kfree(msb);
		}
	}
	mutex_unlock(&msb_disk_lock);
	return 0;
}
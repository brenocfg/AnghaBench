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
struct pcd_unit {int /*<<< orphan*/  info; } ;
struct block_device {TYPE_1__* bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {struct pcd_unit* private_data; } ;

/* Variables and functions */
 int cdrom_open (int /*<<< orphan*/ *,struct block_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_disk_change (struct block_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcd_mutex ; 

__attribute__((used)) static int pcd_block_open(struct block_device *bdev, fmode_t mode)
{
	struct pcd_unit *cd = bdev->bd_disk->private_data;
	int ret;

	check_disk_change(bdev);

	mutex_lock(&pcd_mutex);
	ret = cdrom_open(&cd->info, bdev, mode);
	mutex_unlock(&pcd_mutex);

	return ret;
}
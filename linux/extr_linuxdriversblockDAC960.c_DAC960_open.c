#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct gendisk {scalar_t__ private_data; TYPE_1__* queue; } ;
struct block_device {struct gendisk* bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_10__ {TYPE_5__** LogicalDeviceInformation; } ;
struct TYPE_9__ {TYPE_2__* LogicalDriveInformation; } ;
struct TYPE_12__ {scalar_t__ FirmwareType; int /*<<< orphan*/ * disks; TYPE_4__ V2; TYPE_3__ V1; } ;
struct TYPE_11__ {scalar_t__ LogicalDeviceState; } ;
struct TYPE_8__ {scalar_t__ LogicalDriveState; } ;
struct TYPE_7__ {TYPE_6__* queuedata; } ;
typedef  TYPE_5__ DAC960_V2_LogicalDeviceInfo_T ;
typedef  TYPE_6__ DAC960_Controller_T ;

/* Variables and functions */
 scalar_t__ DAC960_V1_Controller ; 
 scalar_t__ DAC960_V1_LogicalDrive_Offline ; 
 scalar_t__ DAC960_V2_LogicalDevice_Offline ; 
 int /*<<< orphan*/  DAC960_mutex ; 
 int ENXIO ; 
 int /*<<< orphan*/  check_disk_change (struct block_device*) ; 
 int /*<<< orphan*/  get_capacity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int DAC960_open(struct block_device *bdev, fmode_t mode)
{
	struct gendisk *disk = bdev->bd_disk;
	DAC960_Controller_T *p = disk->queue->queuedata;
	int drive_nr = (long)disk->private_data;
	int ret = -ENXIO;

	mutex_lock(&DAC960_mutex);
	if (p->FirmwareType == DAC960_V1_Controller) {
		if (p->V1.LogicalDriveInformation[drive_nr].
		    LogicalDriveState == DAC960_V1_LogicalDrive_Offline)
			goto out;
	} else {
		DAC960_V2_LogicalDeviceInfo_T *i =
			p->V2.LogicalDeviceInformation[drive_nr];
		if (!i || i->LogicalDeviceState == DAC960_V2_LogicalDevice_Offline)
			goto out;
	}

	check_disk_change(bdev);

	if (!get_capacity(p->disks[drive_nr]))
		goto out;
	ret = 0;
out:
	mutex_unlock(&DAC960_mutex);
	return ret;
}
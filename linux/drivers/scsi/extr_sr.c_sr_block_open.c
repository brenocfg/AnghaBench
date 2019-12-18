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
struct scsi_device {int dummy; } ;
struct scsi_cd {int /*<<< orphan*/  cdi; struct scsi_device* device; } ;
struct block_device {int /*<<< orphan*/  bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int ENXIO ; 
 int cdrom_open (int /*<<< orphan*/ *,struct block_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_disk_change (struct block_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_autopm_get_device (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_autopm_put_device (struct scsi_device*) ; 
 struct scsi_cd* scsi_cd_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_cd_put (struct scsi_cd*) ; 
 int /*<<< orphan*/  sr_mutex ; 

__attribute__((used)) static int sr_block_open(struct block_device *bdev, fmode_t mode)
{
	struct scsi_cd *cd;
	struct scsi_device *sdev;
	int ret = -ENXIO;

	cd = scsi_cd_get(bdev->bd_disk);
	if (!cd)
		goto out;

	sdev = cd->device;
	scsi_autopm_get_device(sdev);
	check_disk_change(bdev);

	mutex_lock(&sr_mutex);
	ret = cdrom_open(&cd->cdi, bdev, mode);
	mutex_unlock(&sr_mutex);

	scsi_autopm_put_device(sdev);
	if (ret)
		scsi_cd_put(cd);

out:
	return ret;
}
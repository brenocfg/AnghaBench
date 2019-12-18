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
struct scsi_disk {int /*<<< orphan*/  openers; scalar_t__ write_prot; int /*<<< orphan*/  media_present; struct scsi_device* device; } ;
struct scsi_device {scalar_t__ removable; } ;
struct block_device {int /*<<< orphan*/  bd_disk; } ;
typedef  int fmode_t ;

/* Variables and functions */
 int ENOMEDIUM ; 
 int ENXIO ; 
 int EROFS ; 
 int FMODE_NDELAY ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  SCSI_LOG_HLQUEUE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCSI_REMOVAL_PREVENT ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_disk_change (struct block_device*) ; 
 scalar_t__ scsi_block_when_processing_errors (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_device_online (struct scsi_device*) ; 
 struct scsi_disk* scsi_disk_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_disk_put (struct scsi_disk*) ; 
 int /*<<< orphan*/  scsi_set_medium_removal (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*) ; 

__attribute__((used)) static int sd_open(struct block_device *bdev, fmode_t mode)
{
	struct scsi_disk *sdkp = scsi_disk_get(bdev->bd_disk);
	struct scsi_device *sdev;
	int retval;

	if (!sdkp)
		return -ENXIO;

	SCSI_LOG_HLQUEUE(3, sd_printk(KERN_INFO, sdkp, "sd_open\n"));

	sdev = sdkp->device;

	/*
	 * If the device is in error recovery, wait until it is done.
	 * If the device is offline, then disallow any access to it.
	 */
	retval = -ENXIO;
	if (!scsi_block_when_processing_errors(sdev))
		goto error_out;

	if (sdev->removable || sdkp->write_prot)
		check_disk_change(bdev);

	/*
	 * If the drive is empty, just let the open fail.
	 */
	retval = -ENOMEDIUM;
	if (sdev->removable && !sdkp->media_present && !(mode & FMODE_NDELAY))
		goto error_out;

	/*
	 * If the device has the write protect tab set, have the open fail
	 * if the user expects to be able to write to the thing.
	 */
	retval = -EROFS;
	if (sdkp->write_prot && (mode & FMODE_WRITE))
		goto error_out;

	/*
	 * It is possible that the disk changing stuff resulted in
	 * the device being taken offline.  If this is the case,
	 * report this to the user, and don't pretend that the
	 * open actually succeeded.
	 */
	retval = -ENXIO;
	if (!scsi_device_online(sdev))
		goto error_out;

	if ((atomic_inc_return(&sdkp->openers) == 1) && sdev->removable) {
		if (scsi_block_when_processing_errors(sdev))
			scsi_set_medium_removal(sdev, SCSI_REMOVAL_PREVENT);
	}

	return 0;

error_out:
	scsi_disk_put(sdkp);
	return retval;	
}
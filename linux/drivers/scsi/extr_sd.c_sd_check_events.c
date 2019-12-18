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
struct scsi_sense_hdr {int /*<<< orphan*/  member_0; } ;
struct scsi_disk {int media_present; struct scsi_device* device; } ;
struct scsi_device {int changed; } ;
struct gendisk {int dummy; } ;

/* Variables and functions */
 int DISK_EVENT_MEDIA_CHANGE ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  SCSI_LOG_HLQUEUE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_MAX_RETRIES ; 
 int /*<<< orphan*/  SD_TIMEOUT ; 
 scalar_t__ host_byte (int) ; 
 scalar_t__ media_not_present (struct scsi_disk*,struct scsi_sense_hdr*) ; 
 scalar_t__ scsi_block_when_processing_errors (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_device_online (struct scsi_device*) ; 
 struct scsi_disk* scsi_disk_get (struct gendisk*) ; 
 int /*<<< orphan*/  scsi_disk_put (struct scsi_disk*) ; 
 int scsi_test_unit_ready (struct scsi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*) ; 
 int /*<<< orphan*/  set_media_not_present (struct scsi_disk*) ; 

__attribute__((used)) static unsigned int sd_check_events(struct gendisk *disk, unsigned int clearing)
{
	struct scsi_disk *sdkp = scsi_disk_get(disk);
	struct scsi_device *sdp;
	int retval;

	if (!sdkp)
		return 0;

	sdp = sdkp->device;
	SCSI_LOG_HLQUEUE(3, sd_printk(KERN_INFO, sdkp, "sd_check_events\n"));

	/*
	 * If the device is offline, don't send any commands - just pretend as
	 * if the command failed.  If the device ever comes back online, we
	 * can deal with it then.  It is only because of unrecoverable errors
	 * that we would ever take a device offline in the first place.
	 */
	if (!scsi_device_online(sdp)) {
		set_media_not_present(sdkp);
		goto out;
	}

	/*
	 * Using TEST_UNIT_READY enables differentiation between drive with
	 * no cartridge loaded - NOT READY, drive with changed cartridge -
	 * UNIT ATTENTION, or with same cartridge - GOOD STATUS.
	 *
	 * Drives that auto spin down. eg iomega jaz 1G, will be started
	 * by sd_spinup_disk() from sd_revalidate_disk(), which happens whenever
	 * sd_revalidate() is called.
	 */
	if (scsi_block_when_processing_errors(sdp)) {
		struct scsi_sense_hdr sshdr = { 0, };

		retval = scsi_test_unit_ready(sdp, SD_TIMEOUT, SD_MAX_RETRIES,
					      &sshdr);

		/* failed to execute TUR, assume media not present */
		if (host_byte(retval)) {
			set_media_not_present(sdkp);
			goto out;
		}

		if (media_not_present(sdkp, &sshdr))
			goto out;
	}

	/*
	 * For removable scsi disk we have to recognise the presence
	 * of a disk in the drive.
	 */
	if (!sdkp->media_present)
		sdp->changed = 1;
	sdkp->media_present = 1;
out:
	/*
	 * sdp->changed is set under the following conditions:
	 *
	 *	Medium present state has changed in either direction.
	 *	Device has indicated UNIT_ATTENTION.
	 */
	retval = sdp->changed ? DISK_EVENT_MEDIA_CHANGE : 0;
	sdp->changed = 0;
	scsi_disk_put(sdkp);
	return retval;
}
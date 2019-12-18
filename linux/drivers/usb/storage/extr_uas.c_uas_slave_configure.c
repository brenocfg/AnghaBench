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
struct uas_dev_info {int flags; scalar_t__ qdepth; } ;
struct scsi_device {int no_report_opcodes; int broken_fua; int skip_ms_page_3f; int skip_ms_page_8; int wce_default_on; int fix_capacity; struct uas_dev_info* hostdata; } ;

/* Variables and functions */
 int US_FL_ALWAYS_SYNC ; 
 int US_FL_BROKEN_FUA ; 
 int US_FL_FIX_CAPACITY ; 
 int US_FL_NO_REPORT_OPCODES ; 
 int US_FL_NO_WP_DETECT ; 
 int /*<<< orphan*/  scsi_change_queue_depth (struct scsi_device*,scalar_t__) ; 

__attribute__((used)) static int uas_slave_configure(struct scsi_device *sdev)
{
	struct uas_dev_info *devinfo = sdev->hostdata;

	if (devinfo->flags & US_FL_NO_REPORT_OPCODES)
		sdev->no_report_opcodes = 1;

	/* A few buggy USB-ATA bridges don't understand FUA */
	if (devinfo->flags & US_FL_BROKEN_FUA)
		sdev->broken_fua = 1;

	/* UAS also needs to support FL_ALWAYS_SYNC */
	if (devinfo->flags & US_FL_ALWAYS_SYNC) {
		sdev->skip_ms_page_3f = 1;
		sdev->skip_ms_page_8 = 1;
		sdev->wce_default_on = 1;
	}

	/*
	 * Some disks return the total number of blocks in response
	 * to READ CAPACITY rather than the highest block number.
	 * If this device makes that mistake, tell the sd driver.
	 */
	if (devinfo->flags & US_FL_FIX_CAPACITY)
		sdev->fix_capacity = 1;

	/*
	 * Some devices don't like MODE SENSE with page=0x3f,
	 * which is the command used for checking if a device
	 * is write-protected.  Now that we tell the sd driver
	 * to do a 192-byte transfer with this command the
	 * majority of devices work fine, but a few still can't
	 * handle it.  The sd driver will simply assume those
	 * devices are write-enabled.
	 */
	if (devinfo->flags & US_FL_NO_WP_DETECT)
		sdev->skip_ms_page_3f = 1;

	scsi_change_queue_depth(sdev, devinfo->qdepth - 2);
	return 0;
}
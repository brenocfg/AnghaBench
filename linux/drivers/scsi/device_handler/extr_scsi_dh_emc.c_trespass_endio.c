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
struct scsi_sense_hdr {int sense_key; int asc; int ascq; } ;
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLARIION_NAME ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int SCSI_DH_DEV_FAILED ; 
 int SCSI_DH_DEV_TEMP_BUSY ; 
 int SCSI_DH_IO ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int trespass_endio(struct scsi_device *sdev,
			  struct scsi_sense_hdr *sshdr)
{
	int err = SCSI_DH_IO;

	sdev_printk(KERN_ERR, sdev, "%s: Found valid sense data 0x%2x, "
		    "0x%2x, 0x%2x while sending CLARiiON trespass "
		    "command.\n", CLARIION_NAME, sshdr->sense_key,
		    sshdr->asc, sshdr->ascq);

	if (sshdr->sense_key == 0x05 && sshdr->asc == 0x04 &&
	    sshdr->ascq == 0x00) {
		/*
		 * Array based copy in progress -- do not send
		 * mode_select or copy will be aborted mid-stream.
		 */
		sdev_printk(KERN_INFO, sdev, "%s: Array Based Copy in "
			    "progress while sending CLARiiON trespass "
			    "command.\n", CLARIION_NAME);
		err = SCSI_DH_DEV_TEMP_BUSY;
	} else if (sshdr->sense_key == 0x02 && sshdr->asc == 0x04 &&
		   sshdr->ascq == 0x03) {
		/*
		 * LUN Not Ready - Manual Intervention Required
		 * indicates in-progress ucode upgrade (NDU).
		 */
		sdev_printk(KERN_INFO, sdev, "%s: Detected in-progress "
			    "ucode upgrade NDU operation while sending "
			    "CLARiiON trespass command.\n", CLARIION_NAME);
		err = SCSI_DH_DEV_TEMP_BUSY;
	} else
		err = SCSI_DH_DEV_FAILED;
	return err;
}
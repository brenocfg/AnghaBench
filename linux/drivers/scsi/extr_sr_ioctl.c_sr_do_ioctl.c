#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_sense_hdr {int sense_key; int asc; int ascq; } ;
struct scsi_device {int changed; } ;
struct packet_command {int stat; int /*<<< orphan*/  quiet; int /*<<< orphan*/  timeout; int /*<<< orphan*/  buflen; int /*<<< orphan*/  buffer; int /*<<< orphan*/  data_direction; int /*<<< orphan*/  cmd; struct scsi_sense_hdr* sshdr; } ;
struct TYPE_4__ {struct scsi_device* device; } ;
typedef  TYPE_1__ Scsi_CD ;

/* Variables and functions */
 int EDRIVE_CANT_DO_THIS ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEDIUM ; 
#define  ILLEGAL_REQUEST 130 
 int /*<<< orphan*/  IOCTL_RETRIES ; 
 int /*<<< orphan*/  KERN_INFO ; 
#define  NOT_READY 129 
#define  UNIT_ATTENTION 128 
 scalar_t__ driver_byte (int) ; 
 int /*<<< orphan*/  scsi_block_when_processing_errors (struct scsi_device*) ; 
 int scsi_execute (struct scsi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct scsi_sense_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sr_printk (int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ssleep (int) ; 

int sr_do_ioctl(Scsi_CD *cd, struct packet_command *cgc)
{
	struct scsi_device *SDev;
	struct scsi_sense_hdr local_sshdr, *sshdr = &local_sshdr;
	int result, err = 0, retries = 0;

	SDev = cd->device;

	if (cgc->sshdr)
		sshdr = cgc->sshdr;

      retry:
	if (!scsi_block_when_processing_errors(SDev)) {
		err = -ENODEV;
		goto out;
	}

	result = scsi_execute(SDev, cgc->cmd, cgc->data_direction,
			      cgc->buffer, cgc->buflen, NULL, sshdr,
			      cgc->timeout, IOCTL_RETRIES, 0, 0, NULL);

	/* Minimal error checking.  Ignore cases we know about, and report the rest. */
	if (driver_byte(result) != 0) {
		switch (sshdr->sense_key) {
		case UNIT_ATTENTION:
			SDev->changed = 1;
			if (!cgc->quiet)
				sr_printk(KERN_INFO, cd,
					  "disc change detected.\n");
			if (retries++ < 10)
				goto retry;
			err = -ENOMEDIUM;
			break;
		case NOT_READY:	/* This happens if there is no disc in drive */
			if (sshdr->asc == 0x04 &&
			    sshdr->ascq == 0x01) {
				/* sense: Logical unit is in process of becoming ready */
				if (!cgc->quiet)
					sr_printk(KERN_INFO, cd,
						  "CDROM not ready yet.\n");
				if (retries++ < 10) {
					/* sleep 2 sec and try again */
					ssleep(2);
					goto retry;
				} else {
					/* 20 secs are enough? */
					err = -ENOMEDIUM;
					break;
				}
			}
			if (!cgc->quiet)
				sr_printk(KERN_INFO, cd,
					  "CDROM not ready.  Make sure there "
					  "is a disc in the drive.\n");
			err = -ENOMEDIUM;
			break;
		case ILLEGAL_REQUEST:
			err = -EIO;
			if (sshdr->asc == 0x20 &&
			    sshdr->ascq == 0x00)
				/* sense: Invalid command operation code */
				err = -EDRIVE_CANT_DO_THIS;
			break;
		default:
			err = -EIO;
		}
	}

	/* Wake up a process waiting for device */
      out:
	cgc->stat = err;
	return err;
}
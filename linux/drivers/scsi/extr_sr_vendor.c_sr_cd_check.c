#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct packet_command {int* cmd; unsigned char* buffer; int buflen; int quiet; void* timeout; void* data_direction; } ;
struct cdrom_device_info {int mask; TYPE_3__* handle; } ;
struct TYPE_9__ {int mask; } ;
struct TYPE_10__ {int vendor; unsigned long ms_offset; int xa_flag; TYPE_1__* device; TYPE_2__ cdi; } ;
struct TYPE_8__ {int sector_size; } ;
typedef  TYPE_3__ Scsi_CD ;

/* Variables and functions */
 int CDC_MULTI_SESSION ; 
 scalar_t__ CDS_AUDIO ; 
 unsigned long CD_FRAMES ; 
 unsigned long CD_MSF_OFFSET ; 
 unsigned long CD_SECS ; 
 void* DMA_FROM_DEVICE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 void* READ_TOC ; 
#define  VENDOR_NEC 131 
#define  VENDOR_SCSI3 130 
 void* VENDOR_TIMEOUT ; 
#define  VENDOR_TOSHIBA 129 
#define  VENDOR_WRITER 128 
 unsigned long bcd2bin (unsigned char) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int) ; 
 int /*<<< orphan*/  memset (struct packet_command*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sr_disk_status (struct cdrom_device_info*) ; 
 int sr_do_ioctl (TYPE_3__*,struct packet_command*) ; 
 int sr_is_xa (TYPE_3__*) ; 
 int /*<<< orphan*/  sr_printk (int /*<<< orphan*/ ,TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  sr_set_blocklength (TYPE_3__*,int) ; 

int sr_cd_check(struct cdrom_device_info *cdi)
{
	Scsi_CD *cd = cdi->handle;
	unsigned long sector;
	unsigned char *buffer;	/* the buffer for the ioctl */
	struct packet_command cgc;
	int rc, no_multi;

	if (cd->cdi.mask & CDC_MULTI_SESSION)
		return 0;

	buffer = kmalloc(512, GFP_KERNEL | GFP_DMA);
	if (!buffer)
		return -ENOMEM;

	sector = 0;		/* the multisession sector offset goes here  */
	no_multi = 0;		/* flag: the drive can't handle multisession */
	rc = 0;

	memset(&cgc, 0, sizeof(struct packet_command));

	switch (cd->vendor) {

	case VENDOR_SCSI3:
		cgc.cmd[0] = READ_TOC;
		cgc.cmd[8] = 12;
		cgc.cmd[9] = 0x40;
		cgc.buffer = buffer;
		cgc.buflen = 12;
		cgc.quiet = 1;
		cgc.data_direction = DMA_FROM_DEVICE;
		cgc.timeout = VENDOR_TIMEOUT;
		rc = sr_do_ioctl(cd, &cgc);
		if (rc != 0)
			break;
		if ((buffer[0] << 8) + buffer[1] < 0x0a) {
			sr_printk(KERN_INFO, cd, "Hmm, seems the drive "
			   "doesn't support multisession CD's\n");
			no_multi = 1;
			break;
		}
		sector = buffer[11] + (buffer[10] << 8) +
		    (buffer[9] << 16) + (buffer[8] << 24);
		if (buffer[6] <= 1) {
			/* ignore sector offsets from first track */
			sector = 0;
		}
		break;

#ifdef CONFIG_BLK_DEV_SR_VENDOR
	case VENDOR_NEC:{
			unsigned long min, sec, frame;
			cgc.cmd[0] = 0xde;
			cgc.cmd[1] = 0x03;
			cgc.cmd[2] = 0xb0;
			cgc.buffer = buffer;
			cgc.buflen = 0x16;
			cgc.quiet = 1;
			cgc.data_direction = DMA_FROM_DEVICE;
			cgc.timeout = VENDOR_TIMEOUT;
			rc = sr_do_ioctl(cd, &cgc);
			if (rc != 0)
				break;
			if (buffer[14] != 0 && buffer[14] != 0xb0) {
				sr_printk(KERN_INFO, cd, "Hmm, seems the cdrom "
					  "doesn't support multisession CD's\n");

				no_multi = 1;
				break;
			}
			min = bcd2bin(buffer[15]);
			sec = bcd2bin(buffer[16]);
			frame = bcd2bin(buffer[17]);
			sector = min * CD_SECS * CD_FRAMES + sec * CD_FRAMES + frame;
			break;
		}

	case VENDOR_TOSHIBA:{
			unsigned long min, sec, frame;

			/* we request some disc information (is it a XA-CD ?,
			 * where starts the last session ?) */
			cgc.cmd[0] = 0xc7;
			cgc.cmd[1] = 0x03;
			cgc.buffer = buffer;
			cgc.buflen = 4;
			cgc.quiet = 1;
			cgc.data_direction = DMA_FROM_DEVICE;
			cgc.timeout = VENDOR_TIMEOUT;
			rc = sr_do_ioctl(cd, &cgc);
			if (rc == -EINVAL) {
				sr_printk(KERN_INFO, cd, "Hmm, seems the drive "
					  "doesn't support multisession CD's\n");
				no_multi = 1;
				break;
			}
			if (rc != 0)
				break;
			min = bcd2bin(buffer[1]);
			sec = bcd2bin(buffer[2]);
			frame = bcd2bin(buffer[3]);
			sector = min * CD_SECS * CD_FRAMES + sec * CD_FRAMES + frame;
			if (sector)
				sector -= CD_MSF_OFFSET;
			sr_set_blocklength(cd, 2048);
			break;
		}

	case VENDOR_WRITER:
		cgc.cmd[0] = READ_TOC;
		cgc.cmd[8] = 0x04;
		cgc.cmd[9] = 0x40;
		cgc.buffer = buffer;
		cgc.buflen = 0x04;
		cgc.quiet = 1;
		cgc.data_direction = DMA_FROM_DEVICE;
		cgc.timeout = VENDOR_TIMEOUT;
		rc = sr_do_ioctl(cd, &cgc);
		if (rc != 0) {
			break;
		}
		if ((rc = buffer[2]) == 0) {
			sr_printk(KERN_WARNING, cd,
				  "No finished session\n");
			break;
		}
		cgc.cmd[0] = READ_TOC;	/* Read TOC */
		cgc.cmd[6] = rc & 0x7f;	/* number of last session */
		cgc.cmd[8] = 0x0c;
		cgc.cmd[9] = 0x40;
		cgc.buffer = buffer;
		cgc.buflen = 12;
		cgc.quiet = 1;
		cgc.data_direction = DMA_FROM_DEVICE;
		cgc.timeout = VENDOR_TIMEOUT;
		rc = sr_do_ioctl(cd, &cgc);
		if (rc != 0) {
			break;
		}
		sector = buffer[11] + (buffer[10] << 8) +
		    (buffer[9] << 16) + (buffer[8] << 24);
		break;
#endif				/* CONFIG_BLK_DEV_SR_VENDOR */

	default:
		/* should not happen */
		sr_printk(KERN_WARNING, cd,
			  "unknown vendor code (%i), not initialized ?\n",
			  cd->vendor);
		sector = 0;
		no_multi = 1;
		break;
	}
	cd->ms_offset = sector;
	cd->xa_flag = 0;
	if (CDS_AUDIO != sr_disk_status(cdi) && 1 == sr_is_xa(cd))
		cd->xa_flag = 1;

	if (2048 != cd->device->sector_size) {
		sr_set_blocklength(cd, 2048);
	}
	if (no_multi)
		cdi->mask |= CDC_MULTI_SESSION;

#ifdef DEBUG
	if (sector)
		sr_printk(KERN_DEBUG, cd, "multisession offset=%lu\n",
			  sector);
#endif
	kfree(buffer);
	return rc;
}
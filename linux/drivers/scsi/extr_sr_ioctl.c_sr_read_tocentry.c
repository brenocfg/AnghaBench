#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_cd {int dummy; } ;
struct packet_command {int* cmd; unsigned char* buffer; int buflen; int /*<<< orphan*/  data_direction; int /*<<< orphan*/  timeout; } ;
struct TYPE_3__ {unsigned char minute; unsigned char second; unsigned char frame; } ;
struct TYPE_4__ {unsigned char lba; TYPE_1__ msf; } ;
struct cdrom_tocentry {scalar_t__ cdte_format; int cdte_track; unsigned char cdte_ctrl; unsigned char cdte_adr; int cdte_datamode; TYPE_2__ cdte_addr; } ;
struct cdrom_device_info {struct scsi_cd* handle; } ;

/* Variables and functions */
 scalar_t__ CDROM_MSF ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int GPCMD_READ_TOC_PMA_ATIP ; 
 int /*<<< orphan*/  IOCTL_TIMEOUT ; 
 int SR_GFP_DMA (struct scsi_cd*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int) ; 
 int /*<<< orphan*/  memset (struct packet_command*,int /*<<< orphan*/ ,int) ; 
 int sr_do_ioctl (struct scsi_cd*,struct packet_command*) ; 

__attribute__((used)) static int sr_read_tocentry(struct cdrom_device_info *cdi,
		struct cdrom_tocentry *tocentry)
{
	struct scsi_cd *cd = cdi->handle;
	struct packet_command cgc;
	int result;
	unsigned char *buffer;

	buffer = kmalloc(32, GFP_KERNEL | SR_GFP_DMA(cd));
	if (!buffer)
		return -ENOMEM;

	memset(&cgc, 0, sizeof(struct packet_command));
	cgc.timeout = IOCTL_TIMEOUT;
	cgc.cmd[0] = GPCMD_READ_TOC_PMA_ATIP;
	cgc.cmd[1] |= (tocentry->cdte_format == CDROM_MSF) ? 0x02 : 0;
	cgc.cmd[6] = tocentry->cdte_track;
	cgc.cmd[8] = 12;		/* LSB of length */
	cgc.buffer = buffer;
	cgc.buflen = 12;
	cgc.data_direction = DMA_FROM_DEVICE;

	result = sr_do_ioctl(cd, &cgc);

	tocentry->cdte_ctrl = buffer[5] & 0xf;
	tocentry->cdte_adr = buffer[5] >> 4;
	tocentry->cdte_datamode = (tocentry->cdte_ctrl & 0x04) ? 1 : 0;
	if (tocentry->cdte_format == CDROM_MSF) {
		tocentry->cdte_addr.msf.minute = buffer[9];
		tocentry->cdte_addr.msf.second = buffer[10];
		tocentry->cdte_addr.msf.frame = buffer[11];
	} else
		tocentry->cdte_addr.lba = (((((buffer[8] << 8) + buffer[9]) << 8)
			+ buffer[10]) << 8) + buffer[11];

	kfree(buffer);
	return result;
}
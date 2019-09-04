#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct packet_command {scalar_t__* cmd; int* buffer; } ;
struct TYPE_7__ {int minute; int second; int frame; } ;
struct TYPE_8__ {int lba; TYPE_3__ msf; } ;
struct TYPE_5__ {int minute; int second; int frame; } ;
struct TYPE_6__ {int lba; TYPE_1__ msf; } ;
struct cdrom_subchnl {scalar_t__ cdsc_format; int cdsc_audiostatus; int cdsc_ctrl; int cdsc_trk; int cdsc_ind; TYPE_4__ cdsc_absaddr; TYPE_2__ cdsc_reladdr; } ;
struct cdrom_device_ops {int (* generic_packet ) (struct cdrom_device_info*,struct packet_command*) ;} ;
struct cdrom_device_info {struct cdrom_device_ops* ops; } ;

/* Variables and functions */
 scalar_t__ CDROM_LBA ; 
 int /*<<< orphan*/  CGC_DATA_READ ; 
 scalar_t__ GPCMD_READ_SUBCHANNEL ; 
 int /*<<< orphan*/  init_cdrom_command (struct packet_command*,char*,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct cdrom_device_info*,struct packet_command*) ; 

__attribute__((used)) static int cdrom_read_subchannel(struct cdrom_device_info *cdi,
				 struct cdrom_subchnl *subchnl, int mcn)
{
	const struct cdrom_device_ops *cdo = cdi->ops;
	struct packet_command cgc;
	char buffer[32];
	int ret;

	init_cdrom_command(&cgc, buffer, 16, CGC_DATA_READ);
	cgc.cmd[0] = GPCMD_READ_SUBCHANNEL;
	cgc.cmd[1] = subchnl->cdsc_format;/* MSF or LBA addressing */
	cgc.cmd[2] = 0x40;  /* request subQ data */
	cgc.cmd[3] = mcn ? 2 : 1;
	cgc.cmd[8] = 16;

	if ((ret = cdo->generic_packet(cdi, &cgc)))
		return ret;

	subchnl->cdsc_audiostatus = cgc.buffer[1];
	subchnl->cdsc_ctrl = cgc.buffer[5] & 0xf;
	subchnl->cdsc_trk = cgc.buffer[6];
	subchnl->cdsc_ind = cgc.buffer[7];

	if (subchnl->cdsc_format == CDROM_LBA) {
		subchnl->cdsc_absaddr.lba = ((cgc.buffer[8] << 24) |
						(cgc.buffer[9] << 16) |
						(cgc.buffer[10] << 8) |
						(cgc.buffer[11]));
		subchnl->cdsc_reladdr.lba = ((cgc.buffer[12] << 24) |
						(cgc.buffer[13] << 16) |
						(cgc.buffer[14] << 8) |
						(cgc.buffer[15]));
	} else {
		subchnl->cdsc_reladdr.msf.minute = cgc.buffer[13];
		subchnl->cdsc_reladdr.msf.second = cgc.buffer[14];
		subchnl->cdsc_reladdr.msf.frame = cgc.buffer[15];
		subchnl->cdsc_absaddr.msf.minute = cgc.buffer[9];
		subchnl->cdsc_absaddr.msf.second = cgc.buffer[10];
		subchnl->cdsc_absaddr.msf.frame = cgc.buffer[11];
	}

	return 0;
}
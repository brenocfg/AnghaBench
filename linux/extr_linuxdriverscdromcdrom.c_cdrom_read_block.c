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
struct packet_command {int* cmd; int buflen; } ;
struct cdrom_device_ops {int (* generic_packet ) (struct cdrom_device_info*,struct packet_command*) ;} ;
struct cdrom_device_info {struct cdrom_device_ops* ops; } ;

/* Variables and functions */
#define  CD_FRAMESIZE_RAW 130 
#define  CD_FRAMESIZE_RAW0 129 
#define  CD_FRAMESIZE_RAW1 128 
 int GPCMD_READ_CD ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct cdrom_device_info*,struct packet_command*) ; 

__attribute__((used)) static int cdrom_read_block(struct cdrom_device_info *cdi,
			    struct packet_command *cgc,
			    int lba, int nblocks, int format, int blksize)
{
	const struct cdrom_device_ops *cdo = cdi->ops;

	memset(&cgc->cmd, 0, sizeof(cgc->cmd));
	cgc->cmd[0] = GPCMD_READ_CD;
	/* expected sector size - cdda,mode1,etc. */
	cgc->cmd[1] = format << 2;
	/* starting address */
	cgc->cmd[2] = (lba >> 24) & 0xff;
	cgc->cmd[3] = (lba >> 16) & 0xff;
	cgc->cmd[4] = (lba >>  8) & 0xff;
	cgc->cmd[5] = lba & 0xff;
	/* number of blocks */
	cgc->cmd[6] = (nblocks >> 16) & 0xff;
	cgc->cmd[7] = (nblocks >>  8) & 0xff;
	cgc->cmd[8] = nblocks & 0xff;
	cgc->buflen = blksize * nblocks;
	
	/* set the header info returned */
	switch (blksize) {
	case CD_FRAMESIZE_RAW0	: cgc->cmd[9] = 0x58; break;
	case CD_FRAMESIZE_RAW1	: cgc->cmd[9] = 0x78; break;
	case CD_FRAMESIZE_RAW	: cgc->cmd[9] = 0xf8; break;
	default			: cgc->cmd[9] = 0x10;
	}
	
	return cdo->generic_packet(cdi, cgc);
}
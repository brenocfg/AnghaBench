#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int* cmnd; } ;
struct TYPE_2__ {scalar_t__ wce; scalar_t__ rce; } ;
struct myrs_ldev_info {int cacheline_size; TYPE_1__ ldev_control; int /*<<< orphan*/  devsize_bytes; int /*<<< orphan*/  cfg_devsize; } ;
struct myrs_hba {int dummy; } ;
typedef  int /*<<< orphan*/  modes ;

/* Variables and functions */
 scalar_t__ MYRS_INTELLIGENT_WRITECACHE_ENABLED ; 
 scalar_t__ MYRS_LOGICALDEVICE_RO ; 
 scalar_t__ MYRS_READCACHE_DISABLED ; 
 scalar_t__ MYRS_WRITECACHE_ENABLED ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int,unsigned char*) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  scsi_sg_copy_from_buffer (struct scsi_cmnd*,unsigned char*,size_t) ; 

__attribute__((used)) static void myrs_mode_sense(struct myrs_hba *cs, struct scsi_cmnd *scmd,
		struct myrs_ldev_info *ldev_info)
{
	unsigned char modes[32], *mode_pg;
	bool dbd;
	size_t mode_len;

	dbd = (scmd->cmnd[1] & 0x08) == 0x08;
	if (dbd) {
		mode_len = 24;
		mode_pg = &modes[4];
	} else {
		mode_len = 32;
		mode_pg = &modes[12];
	}
	memset(modes, 0, sizeof(modes));
	modes[0] = mode_len - 1;
	modes[2] = 0x10; /* Enable FUA */
	if (ldev_info->ldev_control.wce == MYRS_LOGICALDEVICE_RO)
		modes[2] |= 0x80;
	if (!dbd) {
		unsigned char *block_desc = &modes[4];

		modes[3] = 8;
		put_unaligned_be32(ldev_info->cfg_devsize, &block_desc[0]);
		put_unaligned_be32(ldev_info->devsize_bytes, &block_desc[5]);
	}
	mode_pg[0] = 0x08;
	mode_pg[1] = 0x12;
	if (ldev_info->ldev_control.rce == MYRS_READCACHE_DISABLED)
		mode_pg[2] |= 0x01;
	if (ldev_info->ldev_control.wce == MYRS_WRITECACHE_ENABLED ||
	    ldev_info->ldev_control.wce == MYRS_INTELLIGENT_WRITECACHE_ENABLED)
		mode_pg[2] |= 0x04;
	if (ldev_info->cacheline_size) {
		mode_pg[2] |= 0x08;
		put_unaligned_be16(1 << ldev_info->cacheline_size,
				   &mode_pg[14]);
	}

	scsi_sg_copy_from_buffer(scmd, modes, mode_len);
}
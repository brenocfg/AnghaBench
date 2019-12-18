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
struct scsi_cmnd {int* cmnd; } ;
struct myrb_ldev_info {scalar_t__ wb_enabled; int /*<<< orphan*/  size; } ;
struct myrb_hba {scalar_t__ segment_size; int /*<<< orphan*/  ldev_block_size; } ;
typedef  int /*<<< orphan*/  modes ;

/* Variables and functions */
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_be16 (scalar_t__,unsigned char*) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  scsi_sg_copy_from_buffer (struct scsi_cmnd*,unsigned char*,size_t) ; 

__attribute__((used)) static void
myrb_mode_sense(struct myrb_hba *cb, struct scsi_cmnd *scmd,
		struct myrb_ldev_info *ldev_info)
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
	if (!dbd) {
		unsigned char *block_desc = &modes[4];

		modes[3] = 8;
		put_unaligned_be32(ldev_info->size, &block_desc[0]);
		put_unaligned_be32(cb->ldev_block_size, &block_desc[5]);
	}
	mode_pg[0] = 0x08;
	mode_pg[1] = 0x12;
	if (ldev_info->wb_enabled)
		mode_pg[2] |= 0x04;
	if (cb->segment_size) {
		mode_pg[2] |= 0x08;
		put_unaligned_be16(cb->segment_size, &mode_pg[14]);
	}

	scsi_sg_copy_from_buffer(scmd, modes, mode_len);
}
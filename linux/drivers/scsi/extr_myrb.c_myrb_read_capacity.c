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
struct scsi_cmnd {TYPE_1__* device; } ;
struct myrb_ldev_info {scalar_t__ size; } ;
struct myrb_hba {scalar_t__ ldev_block_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  sdev_gendev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  put_unaligned_be32 (scalar_t__,unsigned char*) ; 
 int /*<<< orphan*/  scsi_sg_copy_from_buffer (struct scsi_cmnd*,unsigned char*,int) ; 

__attribute__((used)) static void myrb_read_capacity(struct myrb_hba *cb, struct scsi_cmnd *scmd,
		struct myrb_ldev_info *ldev_info)
{
	unsigned char data[8];

	dev_dbg(&scmd->device->sdev_gendev,
		"Capacity %u, blocksize %u\n",
		ldev_info->size, cb->ldev_block_size);
	put_unaligned_be32(ldev_info->size - 1, &data[0]);
	put_unaligned_be32(cb->ldev_block_size, &data[4]);
	scsi_sg_copy_from_buffer(scmd, data, 8);
}
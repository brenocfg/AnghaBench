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
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;TYPE_1__* device; int /*<<< orphan*/  sense_buffer; int /*<<< orphan*/  sc_data_direction; } ;
struct myrb_hba {int /*<<< orphan*/  sg_pool; int /*<<< orphan*/  dcdb_pool; } ;
struct myrb_cmdblk {unsigned short status; scalar_t__ sgl_addr; TYPE_2__* sgl; TYPE_2__* dcdb; scalar_t__ dcdb_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  sense; } ;
struct TYPE_3__ {int /*<<< orphan*/  sdev_gendev; } ;

/* Variables and functions */
 int DID_BAD_TARGET ; 
 int DID_ERROR ; 
 int DID_OK ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  MEDIUM_ERROR ; 
#define  MYRB_STATUS_ACCESS_BEYOND_END_OF_LDRV 134 
#define  MYRB_STATUS_BAD_DATA 133 
#define  MYRB_STATUS_DEVICE_BUSY 132 
#define  MYRB_STATUS_DEVICE_NONRESPONSIVE 131 
#define  MYRB_STATUS_IRRECOVERABLE_DATA_ERROR 130 
#define  MYRB_STATUS_LDRV_NONEXISTENT_OR_OFFLINE 129 
#define  MYRB_STATUS_SUCCESS 128 
 int /*<<< orphan*/  NOT_READY ; 
 int SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,...) ; 
 int /*<<< orphan*/  scsi_build_sense_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void myrb_handle_scsi(struct myrb_hba *cb, struct myrb_cmdblk *cmd_blk,
		struct scsi_cmnd *scmd)
{
	unsigned short status;

	if (!cmd_blk)
		return;

	scsi_dma_unmap(scmd);

	if (cmd_blk->dcdb) {
		memcpy(scmd->sense_buffer, &cmd_blk->dcdb->sense, 64);
		dma_pool_free(cb->dcdb_pool, cmd_blk->dcdb,
			      cmd_blk->dcdb_addr);
		cmd_blk->dcdb = NULL;
	}
	if (cmd_blk->sgl) {
		dma_pool_free(cb->sg_pool, cmd_blk->sgl, cmd_blk->sgl_addr);
		cmd_blk->sgl = NULL;
		cmd_blk->sgl_addr = 0;
	}
	status = cmd_blk->status;
	switch (status) {
	case MYRB_STATUS_SUCCESS:
	case MYRB_STATUS_DEVICE_BUSY:
		scmd->result = (DID_OK << 16) | status;
		break;
	case MYRB_STATUS_BAD_DATA:
		dev_dbg(&scmd->device->sdev_gendev,
			"Bad Data Encountered\n");
		if (scmd->sc_data_direction == DMA_FROM_DEVICE)
			/* Unrecovered read error */
			scsi_build_sense_buffer(0, scmd->sense_buffer,
						MEDIUM_ERROR, 0x11, 0);
		else
			/* Write error */
			scsi_build_sense_buffer(0, scmd->sense_buffer,
						MEDIUM_ERROR, 0x0C, 0);
		scmd->result = (DID_OK << 16) | SAM_STAT_CHECK_CONDITION;
		break;
	case MYRB_STATUS_IRRECOVERABLE_DATA_ERROR:
		scmd_printk(KERN_ERR, scmd, "Irrecoverable Data Error\n");
		if (scmd->sc_data_direction == DMA_FROM_DEVICE)
			/* Unrecovered read error, auto-reallocation failed */
			scsi_build_sense_buffer(0, scmd->sense_buffer,
						MEDIUM_ERROR, 0x11, 0x04);
		else
			/* Write error, auto-reallocation failed */
			scsi_build_sense_buffer(0, scmd->sense_buffer,
						MEDIUM_ERROR, 0x0C, 0x02);
		scmd->result = (DID_OK << 16) | SAM_STAT_CHECK_CONDITION;
		break;
	case MYRB_STATUS_LDRV_NONEXISTENT_OR_OFFLINE:
		dev_dbg(&scmd->device->sdev_gendev,
			    "Logical Drive Nonexistent or Offline");
		scmd->result = (DID_BAD_TARGET << 16);
		break;
	case MYRB_STATUS_ACCESS_BEYOND_END_OF_LDRV:
		dev_dbg(&scmd->device->sdev_gendev,
			    "Attempt to Access Beyond End of Logical Drive");
		/* Logical block address out of range */
		scsi_build_sense_buffer(0, scmd->sense_buffer,
					NOT_READY, 0x21, 0);
		break;
	case MYRB_STATUS_DEVICE_NONRESPONSIVE:
		dev_dbg(&scmd->device->sdev_gendev, "Device nonresponsive\n");
		scmd->result = (DID_BAD_TARGET << 16);
		break;
	default:
		scmd_printk(KERN_ERR, scmd,
			    "Unexpected Error Status %04X", status);
		scmd->result = (DID_ERROR << 16);
		break;
	}
	scmd->scsi_done(scmd);
}
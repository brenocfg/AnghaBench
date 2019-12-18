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
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;int /*<<< orphan*/  sense_buffer; } ;
struct myrs_hba {int /*<<< orphan*/  sg_pool; int /*<<< orphan*/  dcdb_pool; int /*<<< orphan*/  sense_pool; } ;
struct myrs_cmdblk {unsigned char status; unsigned int sense_len; int /*<<< orphan*/  residual; scalar_t__ sgl_addr; int /*<<< orphan*/ * sgl; scalar_t__ dcdb_dma; int /*<<< orphan*/ * dcdb; scalar_t__ sense_addr; int /*<<< orphan*/ * sense; } ;

/* Variables and functions */
 int DID_BAD_TARGET ; 
 int DID_OK ; 
 unsigned char MYRS_STATUS_DEVICE_NON_RESPONSIVE ; 
 unsigned char MYRS_STATUS_DEVICE_NON_RESPONSIVE2 ; 
 unsigned char MYRS_STATUS_FAILED ; 
 unsigned int SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void myrs_handle_scsi(struct myrs_hba *cs, struct myrs_cmdblk *cmd_blk,
		struct scsi_cmnd *scmd)
{
	unsigned char status;

	if (!cmd_blk)
		return;

	scsi_dma_unmap(scmd);
	status = cmd_blk->status;
	if (cmd_blk->sense) {
		if (status == MYRS_STATUS_FAILED && cmd_blk->sense_len) {
			unsigned int sense_len = SCSI_SENSE_BUFFERSIZE;

			if (sense_len > cmd_blk->sense_len)
				sense_len = cmd_blk->sense_len;
			memcpy(scmd->sense_buffer, cmd_blk->sense, sense_len);
		}
		dma_pool_free(cs->sense_pool, cmd_blk->sense,
			      cmd_blk->sense_addr);
		cmd_blk->sense = NULL;
		cmd_blk->sense_addr = 0;
	}
	if (cmd_blk->dcdb) {
		dma_pool_free(cs->dcdb_pool, cmd_blk->dcdb,
			      cmd_blk->dcdb_dma);
		cmd_blk->dcdb = NULL;
		cmd_blk->dcdb_dma = 0;
	}
	if (cmd_blk->sgl) {
		dma_pool_free(cs->sg_pool, cmd_blk->sgl,
			      cmd_blk->sgl_addr);
		cmd_blk->sgl = NULL;
		cmd_blk->sgl_addr = 0;
	}
	if (cmd_blk->residual)
		scsi_set_resid(scmd, cmd_blk->residual);
	if (status == MYRS_STATUS_DEVICE_NON_RESPONSIVE ||
	    status == MYRS_STATUS_DEVICE_NON_RESPONSIVE2)
		scmd->result = (DID_BAD_TARGET << 16);
	else
		scmd->result = (DID_OK << 16) | status;
	scmd->scsi_done(scmd);
}
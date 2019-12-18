#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int /*<<< orphan*/  sc_data_direction; } ;
struct qla_hw_data {int /*<<< orphan*/  ctx_mempool; int /*<<< orphan*/  gbl_dsd_avail; int /*<<< orphan*/  gbl_dsd_inuse; int /*<<< orphan*/  gbl_dsd_list; int /*<<< orphan*/  fcp_cmnd_dma_pool; int /*<<< orphan*/  dl_dma_pool; TYPE_2__* pdev; } ;
struct ct6_dsd {scalar_t__ dsd_use_cnt; int /*<<< orphan*/  dsd_list; int /*<<< orphan*/  fcp_cmnd_dma; struct crc_context* fcp_cmnd; } ;
struct crc_context {int /*<<< orphan*/  crc_ctx_dma; } ;
struct TYPE_10__ {struct ct6_dsd* ct6_ctx; struct crc_context* crc_ctx; } ;
struct TYPE_11__ {TYPE_3__ scmd; } ;
struct TYPE_12__ {int flags; TYPE_4__ u; TYPE_1__* vha; } ;
typedef  TYPE_5__ srb_t ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {struct qla_hw_data* hw; } ;

/* Variables and functions */
 struct scsi_cmnd* GET_CMD_SP (TYPE_5__*) ; 
 int SRB_CRC_CTX_DMA_VALID ; 
 int SRB_CRC_CTX_DSD_VALID ; 
 int SRB_CRC_PROT_DMA_VALID ; 
 int SRB_DMA_VALID ; 
 int SRB_FCP_CMND_DMA_VALID ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct crc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_splice (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_free (struct ct6_dsd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_clean_dsd_pool (struct qla_hw_data*,struct crc_context*) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_prot_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_prot_sglist (struct scsi_cmnd*) ; 

void qla2x00_sp_free_dma(srb_t *sp)
{
	struct qla_hw_data *ha = sp->vha->hw;
	struct scsi_cmnd *cmd = GET_CMD_SP(sp);

	if (sp->flags & SRB_DMA_VALID) {
		scsi_dma_unmap(cmd);
		sp->flags &= ~SRB_DMA_VALID;
	}

	if (sp->flags & SRB_CRC_PROT_DMA_VALID) {
		dma_unmap_sg(&ha->pdev->dev, scsi_prot_sglist(cmd),
		    scsi_prot_sg_count(cmd), cmd->sc_data_direction);
		sp->flags &= ~SRB_CRC_PROT_DMA_VALID;
	}

	if (sp->flags & SRB_CRC_CTX_DSD_VALID) {
		/* List assured to be having elements */
		qla2x00_clean_dsd_pool(ha, sp->u.scmd.crc_ctx);
		sp->flags &= ~SRB_CRC_CTX_DSD_VALID;
	}

	if (sp->flags & SRB_CRC_CTX_DMA_VALID) {
		struct crc_context *ctx0 = sp->u.scmd.crc_ctx;

		dma_pool_free(ha->dl_dma_pool, ctx0, ctx0->crc_ctx_dma);
		sp->flags &= ~SRB_CRC_CTX_DMA_VALID;
	}

	if (sp->flags & SRB_FCP_CMND_DMA_VALID) {
		struct ct6_dsd *ctx1 = sp->u.scmd.ct6_ctx;

		dma_pool_free(ha->fcp_cmnd_dma_pool, ctx1->fcp_cmnd,
		    ctx1->fcp_cmnd_dma);
		list_splice(&ctx1->dsd_list, &ha->gbl_dsd_list);
		ha->gbl_dsd_inuse -= ctx1->dsd_use_cnt;
		ha->gbl_dsd_avail += ctx1->dsd_use_cnt;
		mempool_free(ctx1, ha->ctx_mempool);
	}
}
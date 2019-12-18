#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct scsi_cmnd {TYPE_1__* device; } ;
struct scatterlist {int dummy; } ;
struct qla_tc_param {scalar_t__ blk_sz; int* ctx_dsd_alloced; TYPE_5__* ctx; struct scatterlist* prot_sg; int /*<<< orphan*/  sg; int /*<<< orphan*/  bufflen; } ;
struct qla_hw_data {int /*<<< orphan*/  dl_dma_pool; } ;
struct qla2_sgx {scalar_t__ dma_len; scalar_t__ dma_addr; int /*<<< orphan*/  cur_sg; int /*<<< orphan*/  tot_bytes; TYPE_6__* sp; } ;
struct dsd_dma {scalar_t__ dsd_list_dma; int /*<<< orphan*/  list; void* dsd_addr; } ;
struct dsd64 {void* length; scalar_t__ address; } ;
struct TYPE_11__ {TYPE_2__* crc_ctx; } ;
struct TYPE_12__ {TYPE_3__ scmd; } ;
struct TYPE_14__ {int /*<<< orphan*/  flags; TYPE_4__ u; } ;
typedef  TYPE_6__ srb_t ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_13__ {int /*<<< orphan*/  dsd_list; } ;
struct TYPE_10__ {int /*<<< orphan*/  dsd_list; } ;
struct TYPE_9__ {scalar_t__ sector_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 struct scsi_cmnd* GET_CMD_SP (TYPE_6__*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ QLA_DSDS_PER_IOCB ; 
 int /*<<< orphan*/  SRB_CRC_CTX_DSD_VALID ; 
 void* cpu_to_le32 (scalar_t__) ; 
 void* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  kfree (struct dsd_dma*) ; 
 struct dsd_dma* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct qla2_sgx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_le64 (scalar_t__,scalar_t__*) ; 
 scalar_t__ qla24xx_get_one_block_sg (scalar_t__,struct qla2_sgx*,scalar_t__*) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 struct scatterlist* scsi_prot_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 
 scalar_t__ sg_dma_address (struct scatterlist*) ; 
 scalar_t__ sg_dma_len (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

int
qla24xx_walk_and_build_sglist_no_difb(struct qla_hw_data *ha, srb_t *sp,
	struct dsd64 *dsd, uint16_t tot_dsds, struct qla_tc_param *tc)
{
	void *next_dsd;
	uint8_t avail_dsds = 0;
	uint32_t dsd_list_len;
	struct dsd_dma *dsd_ptr;
	struct scatterlist *sg_prot;
	struct dsd64 *cur_dsd = dsd;
	uint16_t	used_dsds = tot_dsds;
	uint32_t	prot_int; /* protection interval */
	uint32_t	partial;
	struct qla2_sgx sgx;
	dma_addr_t	sle_dma;
	uint32_t	sle_dma_len, tot_prot_dma_len = 0;
	struct scsi_cmnd *cmd;

	memset(&sgx, 0, sizeof(struct qla2_sgx));
	if (sp) {
		cmd = GET_CMD_SP(sp);
		prot_int = cmd->device->sector_size;

		sgx.tot_bytes = scsi_bufflen(cmd);
		sgx.cur_sg = scsi_sglist(cmd);
		sgx.sp = sp;

		sg_prot = scsi_prot_sglist(cmd);
	} else if (tc) {
		prot_int      = tc->blk_sz;
		sgx.tot_bytes = tc->bufflen;
		sgx.cur_sg    = tc->sg;
		sg_prot	      = tc->prot_sg;
	} else {
		BUG();
		return 1;
	}

	while (qla24xx_get_one_block_sg(prot_int, &sgx, &partial)) {

		sle_dma = sgx.dma_addr;
		sle_dma_len = sgx.dma_len;
alloc_and_fill:
		/* Allocate additional continuation packets? */
		if (avail_dsds == 0) {
			avail_dsds = (used_dsds > QLA_DSDS_PER_IOCB) ?
					QLA_DSDS_PER_IOCB : used_dsds;
			dsd_list_len = (avail_dsds + 1) * 12;
			used_dsds -= avail_dsds;

			/* allocate tracking DS */
			dsd_ptr = kzalloc(sizeof(struct dsd_dma), GFP_ATOMIC);
			if (!dsd_ptr)
				return 1;

			/* allocate new list */
			dsd_ptr->dsd_addr = next_dsd =
			    dma_pool_alloc(ha->dl_dma_pool, GFP_ATOMIC,
				&dsd_ptr->dsd_list_dma);

			if (!next_dsd) {
				/*
				 * Need to cleanup only this dsd_ptr, rest
				 * will be done by sp_free_dma()
				 */
				kfree(dsd_ptr);
				return 1;
			}

			if (sp) {
				list_add_tail(&dsd_ptr->list,
					      &sp->u.scmd.crc_ctx->dsd_list);

				sp->flags |= SRB_CRC_CTX_DSD_VALID;
			} else {
				list_add_tail(&dsd_ptr->list,
				    &(tc->ctx->dsd_list));
				*tc->ctx_dsd_alloced = 1;
			}


			/* add new list to cmd iocb or last list */
			put_unaligned_le64(dsd_ptr->dsd_list_dma,
					   &cur_dsd->address);
			cur_dsd->length = cpu_to_le32(dsd_list_len);
			cur_dsd = next_dsd;
		}
		put_unaligned_le64(sle_dma, &cur_dsd->address);
		cur_dsd->length = cpu_to_le32(sle_dma_len);
		cur_dsd++;
		avail_dsds--;

		if (partial == 0) {
			/* Got a full protection interval */
			sle_dma = sg_dma_address(sg_prot) + tot_prot_dma_len;
			sle_dma_len = 8;

			tot_prot_dma_len += sle_dma_len;
			if (tot_prot_dma_len == sg_dma_len(sg_prot)) {
				tot_prot_dma_len = 0;
				sg_prot = sg_next(sg_prot);
			}

			partial = 1; /* So as to not re-enter this block */
			goto alloc_and_fill;
		}
	}
	/* Null termination */
	cur_dsd->address = 0;
	cur_dsd->length = 0;
	cur_dsd++;
	return 0;
}
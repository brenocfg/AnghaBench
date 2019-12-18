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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ulptx_sgl {int dummy; } ;
struct scsi_cmnd {int dummy; } ;
struct TYPE_6__ {scalar_t__* r3_lo; scalar_t__ cp_en_class; scalar_t__ ctl_pri; } ;
struct TYPE_7__ {TYPE_2__ fcoe; } ;
struct fw_scsi_write_wr {uintptr_t cookie; int use_xfer_cnt; TYPE_3__ u; scalar_t__ r4; int /*<<< orphan*/  rsp_dmaaddr; void* rsp_dmalen; void* ini_xfer_cnt; void* xfer_cnt; scalar_t__ tmo_val; int /*<<< orphan*/  iqid; void* flowid_len16; void* op_immdlen; } ;
struct csio_rnode {int /*<<< orphan*/  flowid; } ;
struct csio_dma_buf {int len; int /*<<< orphan*/  paddr; } ;
struct csio_ioreq {struct csio_dma_buf dma_buf; scalar_t__ tmo; int /*<<< orphan*/  iq_idx; struct csio_rnode* rnode; TYPE_1__* lnode; } ;
struct csio_hw {int dummy; } ;
struct TYPE_8__ {scalar_t__ proto_cmd_len; } ;
struct TYPE_5__ {struct csio_hw* hwp; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int) ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FW_SCSI_WRITE_WR ; 
 int FW_SCSI_WRITE_WR_IMMDLEN (scalar_t__) ; 
 int FW_WR_FLOWID_V (int /*<<< orphan*/ ) ; 
 int FW_WR_LEN16_V (int /*<<< orphan*/ ) ; 
 int FW_WR_OP_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 TYPE_4__* csio_hw_to_scsim (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_q_physiqid (struct csio_hw*,int /*<<< orphan*/ ) ; 
 struct scsi_cmnd* csio_scsi_cmnd (struct csio_ioreq*) ; 
 int /*<<< orphan*/  csio_scsi_fcp_cmnd (struct csio_ioreq*,void*) ; 
 int /*<<< orphan*/  csio_scsi_init_ultptx_dsgl (struct csio_hw*,struct csio_ioreq*,struct ulptx_sgl*) ; 
 int scsi_bufflen (struct scsi_cmnd*) ; 

__attribute__((used)) static inline void
csio_scsi_init_write_wr(struct csio_ioreq *req, void *wrp, uint32_t size)
{
	struct csio_hw *hw = req->lnode->hwp;
	struct csio_rnode *rn = req->rnode;
	struct fw_scsi_write_wr *wr = (struct fw_scsi_write_wr *)wrp;
	struct ulptx_sgl *sgl;
	struct csio_dma_buf *dma_buf;
	uint8_t imm = csio_hw_to_scsim(hw)->proto_cmd_len;
	struct scsi_cmnd *scmnd = csio_scsi_cmnd(req);

	wr->op_immdlen = cpu_to_be32(FW_WR_OP_V(FW_SCSI_WRITE_WR) |
				     FW_SCSI_WRITE_WR_IMMDLEN(imm));
	wr->flowid_len16 = cpu_to_be32(FW_WR_FLOWID_V(rn->flowid) |
				       FW_WR_LEN16_V(DIV_ROUND_UP(size, 16)));
	wr->cookie = (uintptr_t)req;
	wr->iqid = cpu_to_be16(csio_q_physiqid(hw, req->iq_idx));
	wr->tmo_val = (uint8_t)(req->tmo);
	wr->use_xfer_cnt = 1;
	wr->xfer_cnt = cpu_to_be32(scsi_bufflen(scmnd));
	wr->ini_xfer_cnt = cpu_to_be32(scsi_bufflen(scmnd));
	/* Get RSP DMA buffer */
	dma_buf = &req->dma_buf;

	/* Prepare RSP SGL */
	wr->rsp_dmalen = cpu_to_be32(dma_buf->len);
	wr->rsp_dmaaddr = cpu_to_be64(dma_buf->paddr);

	wr->r4 = 0;

	wr->u.fcoe.ctl_pri = 0;
	wr->u.fcoe.cp_en_class = 0;
	wr->u.fcoe.r3_lo[0] = 0;
	wr->u.fcoe.r3_lo[1] = 0;
	csio_scsi_fcp_cmnd(req, (void *)((uintptr_t)wrp +
					sizeof(struct fw_scsi_write_wr)));

	/* Move WR pointer past command and immediate data */
	sgl = (struct ulptx_sgl *)((uintptr_t)wrp +
			      sizeof(struct fw_scsi_write_wr) + ALIGN(imm, 16));

	/* Fill in the DSGL */
	csio_scsi_init_ultptx_dsgl(hw, req, sgl);
}
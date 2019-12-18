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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct fw_fcoe_els_ct_wr {int /*<<< orphan*/  rsp_dmaaddr; void* rsp_dmalen; int /*<<< orphan*/  r_id; int /*<<< orphan*/  l_id; void* tmo_val; int /*<<< orphan*/  fl_to_sp; int /*<<< orphan*/  iqid; int /*<<< orphan*/  cookie; scalar_t__ cp_en_class; scalar_t__ ctl_pri; void* els_ct_type; void* flowid_len16; void* op_immdlen; } ;
struct TYPE_4__ {int len; int /*<<< orphan*/  paddr; } ;
struct csio_ioreq {TYPE_2__ dma_buf; scalar_t__ tmo; int /*<<< orphan*/  iq_idx; TYPE_1__* lnode; int /*<<< orphan*/  fw_handle; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  hwp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FW_FCOE_ELS_CT_WR ; 
 int FW_FCOE_ELS_CT_WR_IMMDLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_FCOE_ELS_CT_WR_SP (int) ; 
 int FW_WR_FLOWID_V (int /*<<< orphan*/ ) ; 
 int FW_WR_LEN16_V (int /*<<< orphan*/ ) ; 
 int FW_WR_OP_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_ID_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_q_physiqid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
csio_ln_prep_ecwr(struct csio_ioreq *io_req, uint32_t wr_len,
		      uint32_t immd_len, uint8_t sub_op, uint32_t sid,
		      uint32_t did, uint32_t flow_id, uint8_t *fw_wr)
{
	struct fw_fcoe_els_ct_wr *wr;
	__be32 port_id;

	wr  = (struct fw_fcoe_els_ct_wr *)fw_wr;
	wr->op_immdlen = cpu_to_be32(FW_WR_OP_V(FW_FCOE_ELS_CT_WR) |
				     FW_FCOE_ELS_CT_WR_IMMDLEN(immd_len));

	wr_len =  DIV_ROUND_UP(wr_len, 16);
	wr->flowid_len16 = cpu_to_be32(FW_WR_FLOWID_V(flow_id) |
				       FW_WR_LEN16_V(wr_len));
	wr->els_ct_type = sub_op;
	wr->ctl_pri = 0;
	wr->cp_en_class = 0;
	wr->cookie = io_req->fw_handle;
	wr->iqid = cpu_to_be16(csio_q_physiqid(
					io_req->lnode->hwp, io_req->iq_idx));
	wr->fl_to_sp =  FW_FCOE_ELS_CT_WR_SP(1);
	wr->tmo_val = (uint8_t) io_req->tmo;
	port_id = htonl(sid);
	memcpy(wr->l_id, PORT_ID_PTR(port_id), 3);
	port_id = htonl(did);
	memcpy(wr->r_id, PORT_ID_PTR(port_id), 3);

	/* Prepare RSP SGL */
	wr->rsp_dmalen = cpu_to_be32(io_req->dma_buf.len);
	wr->rsp_dmaaddr = cpu_to_be64(io_req->dma_buf.paddr);
	return 0;
}
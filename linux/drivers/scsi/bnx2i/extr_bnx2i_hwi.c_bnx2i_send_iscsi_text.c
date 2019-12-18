#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  void* u32 ;
struct iscsi_text {int /*<<< orphan*/  cmdsn; int /*<<< orphan*/  ttt; int /*<<< orphan*/  dlength; int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; } ;
struct iscsi_task {int itt; scalar_t__ hdr; } ;
struct bnx2i_text_request {int itt; int num_bds; scalar_t__ cq_index; void* bd_list_addr_hi; void* bd_list_addr_lo; void* resp_buffer; void* resp_bd_list_addr_hi; void* resp_bd_list_addr_lo; void* cmd_sn; void* ttt; int /*<<< orphan*/  data_length; int /*<<< orphan*/  op_attr; int /*<<< orphan*/  op_code; } ;
struct TYPE_6__ {int resp_buf_size; scalar_t__ req_bd_dma; scalar_t__ resp_bd_dma; } ;
struct bnx2i_conn {TYPE_3__ gen_pdu; TYPE_2__* ep; } ;
struct TYPE_4__ {scalar_t__ sq_prod_qe; } ;
struct TYPE_5__ {TYPE_1__ qp; } ;

/* Variables and functions */
 int ISCSI_TASK_TYPE_MPATH ; 
 int ISCSI_TEXT_REQUEST_NUM_RESP_BDS_SHIFT ; 
 int ISCSI_TEXT_REQUEST_RESP_BUFFER_LENGTH_SHIFT ; 
 int ISCSI_TEXT_REQUEST_TYPE_SHIFT ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2i_ring_dbell_update_sq_params (struct bnx2i_conn*,int) ; 
 int /*<<< orphan*/  memset (struct bnx2i_text_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntoh24 (int /*<<< orphan*/ ) ; 

int bnx2i_send_iscsi_text(struct bnx2i_conn *bnx2i_conn,
			  struct iscsi_task *mtask)
{
	struct bnx2i_text_request *text_wqe;
	struct iscsi_text *text_hdr;
	u32 dword;

	text_hdr = (struct iscsi_text *)mtask->hdr;
	text_wqe = (struct bnx2i_text_request *) bnx2i_conn->ep->qp.sq_prod_qe;

	memset(text_wqe, 0, sizeof(struct bnx2i_text_request));

	text_wqe->op_code = text_hdr->opcode;
	text_wqe->op_attr = text_hdr->flags;
	text_wqe->data_length = ntoh24(text_hdr->dlength);
	text_wqe->itt = mtask->itt |
		(ISCSI_TASK_TYPE_MPATH << ISCSI_TEXT_REQUEST_TYPE_SHIFT);
	text_wqe->ttt = be32_to_cpu(text_hdr->ttt);

	text_wqe->cmd_sn = be32_to_cpu(text_hdr->cmdsn);

	text_wqe->resp_bd_list_addr_lo = (u32) bnx2i_conn->gen_pdu.resp_bd_dma;
	text_wqe->resp_bd_list_addr_hi =
			(u32) ((u64) bnx2i_conn->gen_pdu.resp_bd_dma >> 32);

	dword = ((1 << ISCSI_TEXT_REQUEST_NUM_RESP_BDS_SHIFT) |
		 (bnx2i_conn->gen_pdu.resp_buf_size <<
		  ISCSI_TEXT_REQUEST_RESP_BUFFER_LENGTH_SHIFT));
	text_wqe->resp_buffer = dword;
	text_wqe->bd_list_addr_lo = (u32) bnx2i_conn->gen_pdu.req_bd_dma;
	text_wqe->bd_list_addr_hi =
			(u32) ((u64) bnx2i_conn->gen_pdu.req_bd_dma >> 32);
	text_wqe->num_bds = 1;
	text_wqe->cq_index = 0; /* CQ# used for completion, 5771x only */

	bnx2i_ring_dbell_update_sq_params(bnx2i_conn, 1);
	return 0;
}
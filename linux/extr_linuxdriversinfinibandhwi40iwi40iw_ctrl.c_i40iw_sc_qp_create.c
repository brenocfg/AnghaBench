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
struct TYPE_6__ {int qp_id; } ;
struct i40iw_sc_qp {int qp_type; int virtual_map; TYPE_3__ qp_uk; int /*<<< orphan*/  shadow_area_pa; int /*<<< orphan*/  hw_host_ctx_pa; TYPE_2__* pd; } ;
struct i40iw_sc_cqp {int polarity; int /*<<< orphan*/  dev; } ;
struct i40iw_create_qp_info {int tcp_ctx_valid; int cq_num_valid; int arp_cache_idx_valid; int next_iwarp_state; scalar_t__ ord_valid; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {struct i40iw_sc_cqp* cqp; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_CQPSQ_OPCODE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QP_ARPTABIDXVALID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QP_CQNUMVALID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QP_NEXTIWSTATE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QP_ORDVALID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QP_QPTYPE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QP_TOECTXVALID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QP_VQ ; 
 int /*<<< orphan*/  I40IW_CQPSQ_WQEVALID ; 
 int I40IW_CQP_OP_CREATE_QP ; 
 int I40IW_CQP_WQE_SIZE ; 
 int /*<<< orphan*/  I40IW_DEBUG_WQE ; 
 int I40IW_ERR_INVALID_QP_ID ; 
 int I40IW_ERR_RING_FULL ; 
 int I40IW_MAX_IW_QP_ID ; 
 int I40IW_MIN_IW_QP_ID ; 
 int LS_64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_debug_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  i40iw_insert_wqe_hdr (int*,int) ; 
 int* i40iw_sc_cqp_get_next_send_wqe (struct i40iw_sc_cqp*,int) ; 
 int /*<<< orphan*/  i40iw_sc_cqp_post_sq (struct i40iw_sc_cqp*) ; 
 int /*<<< orphan*/  set_64bit_val (int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_sc_qp_create(
				struct i40iw_sc_qp *qp,
				struct i40iw_create_qp_info *info,
				u64 scratch,
				bool post_sq)
{
	struct i40iw_sc_cqp *cqp;
	u64 *wqe;
	u64 header;

	if ((qp->qp_uk.qp_id < I40IW_MIN_IW_QP_ID) ||
	    (qp->qp_uk.qp_id > I40IW_MAX_IW_QP_ID))
		return I40IW_ERR_INVALID_QP_ID;

	cqp = qp->pd->dev->cqp;
	wqe = i40iw_sc_cqp_get_next_send_wqe(cqp, scratch);
	if (!wqe)
		return I40IW_ERR_RING_FULL;

	set_64bit_val(wqe, 16, qp->hw_host_ctx_pa);

	set_64bit_val(wqe, 40, qp->shadow_area_pa);

	header = qp->qp_uk.qp_id |
		 LS_64(I40IW_CQP_OP_CREATE_QP, I40IW_CQPSQ_OPCODE) |
		 LS_64((info->ord_valid ? 1 : 0), I40IW_CQPSQ_QP_ORDVALID) |
		 LS_64(info->tcp_ctx_valid, I40IW_CQPSQ_QP_TOECTXVALID) |
		 LS_64(qp->qp_type, I40IW_CQPSQ_QP_QPTYPE) |
		 LS_64(qp->virtual_map, I40IW_CQPSQ_QP_VQ) |
		 LS_64(info->cq_num_valid, I40IW_CQPSQ_QP_CQNUMVALID) |
		 LS_64(info->arp_cache_idx_valid, I40IW_CQPSQ_QP_ARPTABIDXVALID) |
		 LS_64(info->next_iwarp_state, I40IW_CQPSQ_QP_NEXTIWSTATE) |
		 LS_64(cqp->polarity, I40IW_CQPSQ_WQEVALID);

	i40iw_insert_wqe_hdr(wqe, header);
	i40iw_debug_buf(cqp->dev, I40IW_DEBUG_WQE, "QP_CREATE WQE",
			wqe, I40IW_CQP_WQE_SIZE * 8);

	if (post_sq)
		i40iw_sc_cqp_post_sq(cqp);
	return 0;
}
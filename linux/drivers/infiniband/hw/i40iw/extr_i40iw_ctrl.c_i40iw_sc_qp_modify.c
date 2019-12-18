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
typedef  scalar_t__ u8 ;
typedef  int u64 ;
struct TYPE_6__ {int qp_id; } ;
struct i40iw_sc_qp {int hw_host_ctx_pa; int shadow_area_pa; scalar_t__ virtual_map; scalar_t__ qp_type; TYPE_3__ qp_uk; TYPE_2__* pd; } ;
struct i40iw_sc_cqp {scalar_t__ polarity; int /*<<< orphan*/  dev; } ;
struct i40iw_modify_qp_info {scalar_t__ next_iwarp_state; scalar_t__ termlen; scalar_t__ ord_valid; scalar_t__ tcp_ctx_valid; scalar_t__ cached_var_valid; scalar_t__ cq_num_valid; scalar_t__ force_loopback; scalar_t__ remove_hash_idx; scalar_t__ reset_tcp_conn; scalar_t__ arp_cache_idx_valid; scalar_t__ dont_send_term; scalar_t__ dont_send_fin; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {struct i40iw_sc_cqp* cqp; } ;

/* Variables and functions */
 scalar_t__ I40IWQP_TERM_SEND_FIN_ONLY ; 
 scalar_t__ I40IWQP_TERM_SEND_TERM_AND_FIN ; 
 scalar_t__ I40IWQP_TERM_SEND_TERM_ONLY ; 
 int /*<<< orphan*/  I40IW_CQPSQ_OPCODE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QP_ARPTABIDXVALID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QP_CACHEDVARVALID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QP_CQNUMVALID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QP_FORCELOOPBACK ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QP_NEXTIWSTATE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QP_ORDVALID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QP_QPTYPE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QP_REMOVEHASHENTRY ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QP_RESETCON ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QP_TERMACT ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QP_TERMLEN ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QP_TOECTXVALID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QP_VQ ; 
 int /*<<< orphan*/  I40IW_CQPSQ_WQEVALID ; 
 scalar_t__ I40IW_CQP_OP_MODIFY_QP ; 
 int I40IW_CQP_WQE_SIZE ; 
 int /*<<< orphan*/  I40IW_DEBUG_WQE ; 
 int I40IW_ERR_RING_FULL ; 
 scalar_t__ I40IW_QP_STATE_TERMINATE ; 
 int LS_64 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_debug_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  i40iw_insert_wqe_hdr (int*,int) ; 
 int* i40iw_sc_cqp_get_next_send_wqe (struct i40iw_sc_cqp*,int) ; 
 int /*<<< orphan*/  i40iw_sc_cqp_post_sq (struct i40iw_sc_cqp*) ; 
 int /*<<< orphan*/  set_64bit_val (int*,int,int) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_sc_qp_modify(
				struct i40iw_sc_qp *qp,
				struct i40iw_modify_qp_info *info,
				u64 scratch,
				bool post_sq)
{
	u64 *wqe;
	struct i40iw_sc_cqp *cqp;
	u64 header;
	u8 term_actions = 0;
	u8 term_len = 0;

	cqp = qp->pd->dev->cqp;
	wqe = i40iw_sc_cqp_get_next_send_wqe(cqp, scratch);
	if (!wqe)
		return I40IW_ERR_RING_FULL;
	if (info->next_iwarp_state == I40IW_QP_STATE_TERMINATE) {
		if (info->dont_send_fin)
			term_actions += I40IWQP_TERM_SEND_TERM_ONLY;
		if (info->dont_send_term)
			term_actions += I40IWQP_TERM_SEND_FIN_ONLY;
		if ((term_actions == I40IWQP_TERM_SEND_TERM_AND_FIN) ||
		    (term_actions == I40IWQP_TERM_SEND_TERM_ONLY))
			term_len = info->termlen;
	}

	set_64bit_val(wqe,
		      8,
		      LS_64(term_len, I40IW_CQPSQ_QP_TERMLEN));

	set_64bit_val(wqe, 16, qp->hw_host_ctx_pa);
	set_64bit_val(wqe, 40, qp->shadow_area_pa);

	header = qp->qp_uk.qp_id |
		 LS_64(I40IW_CQP_OP_MODIFY_QP, I40IW_CQPSQ_OPCODE) |
		 LS_64(info->ord_valid, I40IW_CQPSQ_QP_ORDVALID) |
		 LS_64(info->tcp_ctx_valid, I40IW_CQPSQ_QP_TOECTXVALID) |
		 LS_64(info->cached_var_valid, I40IW_CQPSQ_QP_CACHEDVARVALID) |
		 LS_64(qp->virtual_map, I40IW_CQPSQ_QP_VQ) |
		 LS_64(info->cq_num_valid, I40IW_CQPSQ_QP_CQNUMVALID) |
		 LS_64(info->force_loopback, I40IW_CQPSQ_QP_FORCELOOPBACK) |
		 LS_64(qp->qp_type, I40IW_CQPSQ_QP_QPTYPE) |
		 LS_64(info->remove_hash_idx, I40IW_CQPSQ_QP_REMOVEHASHENTRY) |
		 LS_64(term_actions, I40IW_CQPSQ_QP_TERMACT) |
		 LS_64(info->reset_tcp_conn, I40IW_CQPSQ_QP_RESETCON) |
		 LS_64(info->arp_cache_idx_valid, I40IW_CQPSQ_QP_ARPTABIDXVALID) |
		 LS_64(info->next_iwarp_state, I40IW_CQPSQ_QP_NEXTIWSTATE) |
		 LS_64(cqp->polarity, I40IW_CQPSQ_WQEVALID);

	i40iw_insert_wqe_hdr(wqe, header);

	i40iw_debug_buf(cqp->dev, I40IW_DEBUG_WQE, "QP_MODIFY WQE",
			wqe, I40IW_CQP_WQE_SIZE * 8);

	if (post_sq)
		i40iw_sc_cqp_post_sq(cqp);
	return 0;
}
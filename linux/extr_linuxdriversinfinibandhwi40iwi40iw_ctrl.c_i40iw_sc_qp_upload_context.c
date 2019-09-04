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
typedef  int u64 ;
struct i40iw_upload_context_info {int /*<<< orphan*/  freeze_qp; int /*<<< orphan*/  raw_format; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  qp_id; int /*<<< orphan*/  buf_pa; } ;
struct i40iw_sc_dev {struct i40iw_sc_cqp* cqp; } ;
struct i40iw_sc_cqp {int /*<<< orphan*/  polarity; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_CQPSQ_OPCODE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_UCTX_FREEZEQP ; 
 int /*<<< orphan*/  I40IW_CQPSQ_UCTX_QPID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_UCTX_QPTYPE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_UCTX_RAWFORMAT ; 
 int /*<<< orphan*/  I40IW_CQPSQ_WQEVALID ; 
 int /*<<< orphan*/  I40IW_CQP_OP_UPLOAD_CONTEXT ; 
 int I40IW_CQP_WQE_SIZE ; 
 int /*<<< orphan*/  I40IW_DEBUG_WQE ; 
 int I40IW_ERR_RING_FULL ; 
 int LS_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_debug_buf (struct i40iw_sc_dev*,int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  i40iw_insert_wqe_hdr (int*,int) ; 
 int* i40iw_sc_cqp_get_next_send_wqe (struct i40iw_sc_cqp*,int) ; 
 int /*<<< orphan*/  i40iw_sc_cqp_post_sq (struct i40iw_sc_cqp*) ; 
 int /*<<< orphan*/  set_64bit_val (int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_sc_qp_upload_context(
					struct i40iw_sc_dev *dev,
					struct i40iw_upload_context_info *info,
					u64 scratch,
					bool post_sq)
{
	u64 *wqe;
	struct i40iw_sc_cqp *cqp;
	u64 header;

	cqp = dev->cqp;
	wqe = i40iw_sc_cqp_get_next_send_wqe(cqp, scratch);
	if (!wqe)
		return I40IW_ERR_RING_FULL;
	set_64bit_val(wqe, 16, info->buf_pa);

	header = LS_64(info->qp_id, I40IW_CQPSQ_UCTX_QPID) |
		 LS_64(I40IW_CQP_OP_UPLOAD_CONTEXT, I40IW_CQPSQ_OPCODE) |
		 LS_64(info->qp_type, I40IW_CQPSQ_UCTX_QPTYPE) |
		 LS_64(info->raw_format, I40IW_CQPSQ_UCTX_RAWFORMAT) |
		 LS_64(info->freeze_qp, I40IW_CQPSQ_UCTX_FREEZEQP) |
		 LS_64(cqp->polarity, I40IW_CQPSQ_WQEVALID);

	i40iw_insert_wqe_hdr(wqe, header);

	i40iw_debug_buf(dev, I40IW_DEBUG_WQE, "QP_UPLOAD_CTX WQE",
			wqe, I40IW_CQP_WQE_SIZE * 8);

	if (post_sq)
		i40iw_sc_cqp_post_sq(cqp);
	return 0;
}
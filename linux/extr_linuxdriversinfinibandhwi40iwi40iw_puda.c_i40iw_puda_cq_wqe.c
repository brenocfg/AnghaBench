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
typedef  int u64 ;
struct i40iw_sc_dev {struct i40iw_sc_cqp* cqp; TYPE_2__* cqp_ops; } ;
struct i40iw_sc_cqp {int polarity; } ;
struct TYPE_3__ {int cq_size; int cq_id; } ;
struct i40iw_sc_cq {int shadow_read_threshold; int cq_pa; int shadow_area_pa; TYPE_1__ cq_uk; } ;
struct i40iw_ccq_cqe_info {int dummy; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_4__ {int (* poll_for_cqp_op_done ) (struct i40iw_sc_cqp*,int,struct i40iw_ccq_cqe_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_CQPSQ_CQ_CEQIDVALID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_CQ_CHKOVERFLOW ; 
 int /*<<< orphan*/  I40IW_CQPSQ_CQ_ENCEQEMASK ; 
 int /*<<< orphan*/  I40IW_CQPSQ_CQ_SHADOW_READ_THRESHOLD ; 
 int /*<<< orphan*/  I40IW_CQPSQ_OPCODE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_WQEVALID ; 
 int I40IW_CQP_OP_CREATE_CQ ; 
 int I40IW_CQP_WQE_SIZE ; 
 int /*<<< orphan*/  I40IW_DEBUG_PUDA ; 
 int I40IW_ERR_RING_FULL ; 
 int LS_64 (int,int /*<<< orphan*/ ) ; 
 int RS_64_1 (struct i40iw_sc_cq*,int) ; 
 int /*<<< orphan*/  i40iw_debug_buf (struct i40iw_sc_dev*,int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  i40iw_insert_wqe_hdr (int*,int) ; 
 int* i40iw_sc_cqp_get_next_send_wqe (struct i40iw_sc_cqp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_sc_cqp_post_sq (struct i40iw_sc_cqp*) ; 
 int /*<<< orphan*/  set_64bit_val (int*,int,int) ; 
 int stub1 (struct i40iw_sc_cqp*,int,struct i40iw_ccq_cqe_info*) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_puda_cq_wqe(struct i40iw_sc_dev *dev, struct i40iw_sc_cq *cq)
{
	u64 *wqe;
	struct i40iw_sc_cqp *cqp;
	u64 header;
	struct i40iw_ccq_cqe_info compl_info;
	enum i40iw_status_code status = 0;

	cqp = dev->cqp;
	wqe = i40iw_sc_cqp_get_next_send_wqe(cqp, 0);
	if (!wqe)
		return I40IW_ERR_RING_FULL;

	set_64bit_val(wqe, 0, cq->cq_uk.cq_size);
	set_64bit_val(wqe, 8, RS_64_1(cq, 1));
	set_64bit_val(wqe, 16,
		      LS_64(cq->shadow_read_threshold,
			    I40IW_CQPSQ_CQ_SHADOW_READ_THRESHOLD));
	set_64bit_val(wqe, 32, cq->cq_pa);

	set_64bit_val(wqe, 40, cq->shadow_area_pa);

	header = cq->cq_uk.cq_id |
	    LS_64(I40IW_CQP_OP_CREATE_CQ, I40IW_CQPSQ_OPCODE) |
	    LS_64(1, I40IW_CQPSQ_CQ_CHKOVERFLOW) |
	    LS_64(1, I40IW_CQPSQ_CQ_ENCEQEMASK) |
	    LS_64(1, I40IW_CQPSQ_CQ_CEQIDVALID) |
	    LS_64(cqp->polarity, I40IW_CQPSQ_WQEVALID);
	i40iw_insert_wqe_hdr(wqe, header);

	i40iw_debug_buf(dev, I40IW_DEBUG_PUDA, "PUDA CQE",
			wqe, I40IW_CQP_WQE_SIZE * 8);

	i40iw_sc_cqp_post_sq(dev->cqp);
	status = dev->cqp_ops->poll_for_cqp_op_done(dev->cqp,
						 I40IW_CQP_OP_CREATE_CQ,
						 &compl_info);
	return status;
}
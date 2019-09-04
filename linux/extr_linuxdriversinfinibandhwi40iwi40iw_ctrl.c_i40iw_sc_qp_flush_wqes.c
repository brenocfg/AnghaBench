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
struct i40iw_sc_qp {int flush_rq; int flush_sq; TYPE_3__ qp_uk; TYPE_2__* pd; } ;
struct i40iw_sc_cqp {int polarity; int /*<<< orphan*/  dev; } ;
struct i40iw_qp_flush_info {int userflushcode; int rq_minor_code; int rq_major_code; int sq_minor_code; int sq_major_code; int generate_ae; int ae_code; int ae_source; scalar_t__ sq; scalar_t__ rq; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {struct i40iw_sc_cqp* cqp; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_CQPSQ_FWQE_AESOURCE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_FWQE_FLUSHRQ ; 
 int /*<<< orphan*/  I40IW_CQPSQ_FWQE_FLUSHSQ ; 
 int /*<<< orphan*/  I40IW_CQPSQ_FWQE_GENERATE_AE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_FWQE_RQMJERR ; 
 int /*<<< orphan*/  I40IW_CQPSQ_FWQE_RQMNERR ; 
 int /*<<< orphan*/  I40IW_CQPSQ_FWQE_SQMJERR ; 
 int /*<<< orphan*/  I40IW_CQPSQ_FWQE_SQMNERR ; 
 int /*<<< orphan*/  I40IW_CQPSQ_FWQE_USERFLCODE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_OPCODE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_WQEVALID ; 
 int I40IW_CQP_OP_FLUSH_WQES ; 
 int I40IW_CQP_WQE_SIZE ; 
 int /*<<< orphan*/  I40IW_DEBUG_WQE ; 
 int I40IW_ERR_RING_FULL ; 
 int LS_64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_debug_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  i40iw_insert_wqe_hdr (int*,int) ; 
 int* i40iw_sc_cqp_get_next_send_wqe (struct i40iw_sc_cqp*,int) ; 
 int /*<<< orphan*/  i40iw_sc_cqp_post_sq (struct i40iw_sc_cqp*) ; 
 int /*<<< orphan*/  set_64bit_val (int*,int,int) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_sc_qp_flush_wqes(
				struct i40iw_sc_qp *qp,
				struct i40iw_qp_flush_info *info,
				u64 scratch,
				bool post_sq)
{
	u64 temp = 0;
	u64 *wqe;
	struct i40iw_sc_cqp *cqp;
	u64 header;
	bool flush_sq = false, flush_rq = false;

	if (info->rq && !qp->flush_rq)
		flush_rq = true;

	if (info->sq && !qp->flush_sq)
		flush_sq = true;

	qp->flush_sq |= flush_sq;
	qp->flush_rq |= flush_rq;
	if (!flush_sq && !flush_rq)
		return 0;

	cqp = qp->pd->dev->cqp;
	wqe = i40iw_sc_cqp_get_next_send_wqe(cqp, scratch);
	if (!wqe)
		return I40IW_ERR_RING_FULL;
	if (info->userflushcode) {
		if (flush_rq) {
			temp |= LS_64(info->rq_minor_code, I40IW_CQPSQ_FWQE_RQMNERR) |
				LS_64(info->rq_major_code, I40IW_CQPSQ_FWQE_RQMJERR);
		}
		if (flush_sq) {
			temp |= LS_64(info->sq_minor_code, I40IW_CQPSQ_FWQE_SQMNERR) |
				LS_64(info->sq_major_code, I40IW_CQPSQ_FWQE_SQMJERR);
		}
	}
	set_64bit_val(wqe, 16, temp);

	temp = (info->generate_ae) ?
		info->ae_code | LS_64(info->ae_source, I40IW_CQPSQ_FWQE_AESOURCE) : 0;

	set_64bit_val(wqe, 8, temp);

	header = qp->qp_uk.qp_id |
		 LS_64(I40IW_CQP_OP_FLUSH_WQES, I40IW_CQPSQ_OPCODE) |
		 LS_64(info->generate_ae, I40IW_CQPSQ_FWQE_GENERATE_AE) |
		 LS_64(info->userflushcode, I40IW_CQPSQ_FWQE_USERFLCODE) |
		 LS_64(flush_sq, I40IW_CQPSQ_FWQE_FLUSHSQ) |
		 LS_64(flush_rq, I40IW_CQPSQ_FWQE_FLUSHRQ) |
		 LS_64(cqp->polarity, I40IW_CQPSQ_WQEVALID);

	i40iw_insert_wqe_hdr(wqe, header);

	i40iw_debug_buf(cqp->dev, I40IW_DEBUG_WQE, "QP_FLUSH WQE",
			wqe, I40IW_CQP_WQE_SIZE * 8);

	if (post_sq)
		i40iw_sc_cqp_post_sq(cqp);
	return 0;
}
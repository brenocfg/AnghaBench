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
typedef  int u8 ;
typedef  int u32 ;
struct i40iw_qp_uk_init_info {scalar_t__ max_sq_frag_cnt; scalar_t__ max_rq_frag_cnt; int sq_size; int rq_size; int abi_ver; int /*<<< orphan*/  push_wqe; int /*<<< orphan*/  push_db; int /*<<< orphan*/  qp_id; int /*<<< orphan*/  wqe_alloc_reg; int /*<<< orphan*/  rq_wrid_array; int /*<<< orphan*/  sq_wrtrk_array; int /*<<< orphan*/  shadow_area; int /*<<< orphan*/  rq; int /*<<< orphan*/  sq; int /*<<< orphan*/  max_inline_data; } ;
struct i40iw_qp_uk {int sq_size; scalar_t__ max_sq_frag_cnt; int swqe_polarity; int first_sq_wq; int swqe_polarity_deferred; int rq_size; scalar_t__ max_rq_frag_cnt; int rq_wqe_size; int rq_wqe_size_multiplier; int /*<<< orphan*/  ops; int /*<<< orphan*/  rq_ring; int /*<<< orphan*/  use_srq; scalar_t__ rwqe_polarity; int /*<<< orphan*/  initial_ring; int /*<<< orphan*/  sq_ring; int /*<<< orphan*/  push_wqe; int /*<<< orphan*/  push_db; int /*<<< orphan*/  qp_id; int /*<<< orphan*/  wqe_alloc_reg; int /*<<< orphan*/  rq_wrid_array; int /*<<< orphan*/  sq_wrtrk_array; int /*<<< orphan*/  shadow_area; int /*<<< orphan*/  rq_base; int /*<<< orphan*/  sq_base; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int I40IW_ERR_INVALID_FRAG_COUNT ; 
 int I40IW_MAX_RQ_WQE_SHIFT ; 
 scalar_t__ I40IW_MAX_WQ_FRAGMENT_COUNT ; 
 int /*<<< orphan*/  I40IW_RING_INIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I40IW_RING_MOVE_HEAD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I40IW_RING_MOVE_TAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_get_wqe_shift (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  iw_qp_uk_ops ; 

enum i40iw_status_code i40iw_qp_uk_init(struct i40iw_qp_uk *qp,
					struct i40iw_qp_uk_init_info *info)
{
	enum i40iw_status_code ret_code = 0;
	u32 sq_ring_size;
	u8 sqshift, rqshift;

	if (info->max_sq_frag_cnt > I40IW_MAX_WQ_FRAGMENT_COUNT)
		return I40IW_ERR_INVALID_FRAG_COUNT;

	if (info->max_rq_frag_cnt > I40IW_MAX_WQ_FRAGMENT_COUNT)
		return I40IW_ERR_INVALID_FRAG_COUNT;
	i40iw_get_wqe_shift(info->max_sq_frag_cnt, info->max_inline_data, &sqshift);

	qp->sq_base = info->sq;
	qp->rq_base = info->rq;
	qp->shadow_area = info->shadow_area;
	qp->sq_wrtrk_array = info->sq_wrtrk_array;
	qp->rq_wrid_array = info->rq_wrid_array;

	qp->wqe_alloc_reg = info->wqe_alloc_reg;
	qp->qp_id = info->qp_id;

	qp->sq_size = info->sq_size;
	qp->push_db = info->push_db;
	qp->push_wqe = info->push_wqe;

	qp->max_sq_frag_cnt = info->max_sq_frag_cnt;
	sq_ring_size = qp->sq_size << sqshift;

	I40IW_RING_INIT(qp->sq_ring, sq_ring_size);
	I40IW_RING_INIT(qp->initial_ring, sq_ring_size);
	I40IW_RING_MOVE_HEAD(qp->sq_ring, ret_code);
	I40IW_RING_MOVE_TAIL(qp->sq_ring);
	I40IW_RING_MOVE_HEAD(qp->initial_ring, ret_code);
	qp->swqe_polarity = 1;
	qp->first_sq_wq = true;
	qp->swqe_polarity_deferred = 1;
	qp->rwqe_polarity = 0;

	if (!qp->use_srq) {
		qp->rq_size = info->rq_size;
		qp->max_rq_frag_cnt = info->max_rq_frag_cnt;
		I40IW_RING_INIT(qp->rq_ring, qp->rq_size);
		switch (info->abi_ver) {
		case 4:
			i40iw_get_wqe_shift(info->max_rq_frag_cnt, 0, &rqshift);
			break;
		case 5: /* fallthrough until next ABI version */
		default:
			rqshift = I40IW_MAX_RQ_WQE_SHIFT;
			break;
		}
		qp->rq_wqe_size = rqshift;
		qp->rq_wqe_size_multiplier = 4 << rqshift;
	}
	qp->ops = iw_qp_uk_ops;

	return ret_code;
}
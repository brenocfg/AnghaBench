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
typedef  scalar_t__ wqe_ptr ;
typedef  scalar_t__ u8 ;
typedef  uintptr_t u64 ;
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct i40iw_qp_uk {int swqe_polarity; TYPE_2__* sq_wrtrk_array; TYPE_1__* sq_base; int /*<<< orphan*/  sq_ring; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_4__ {uintptr_t wrid; size_t wr_len; scalar_t__ wqe_size; } ;
struct TYPE_3__ {uintptr_t* elem; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IWQPSQ_VALID ; 
 scalar_t__ I40IW_QP_WQE_MAX_SIZE ; 
 scalar_t__ I40IW_QP_WQE_MIN_SIZE ; 
 size_t I40IW_RING_GETCURRENT_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40IW_RING_MOVE_HEAD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I40IW_RING_MOVE_HEAD_BY_COUNT (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ I40IW_WQE_SIZE_64 ; 
 uintptr_t LS_64 (int,int /*<<< orphan*/ ) ; 
 int RS_64 (uintptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_nop_1 (struct i40iw_qp_uk*) ; 

u64 *i40iw_qp_get_next_send_wqe(struct i40iw_qp_uk *qp,
				u32 *wqe_idx,
				u8 wqe_size,
				u32 total_size,
				u64 wr_id
				)
{
	u64 *wqe = NULL;
	u64 wqe_ptr;
	u32 peek_head = 0;
	u16 offset;
	enum i40iw_status_code ret_code = 0;
	u8 nop_wqe_cnt = 0, i;
	u64 *wqe_0 = NULL;

	*wqe_idx = I40IW_RING_GETCURRENT_HEAD(qp->sq_ring);

	if (!*wqe_idx)
		qp->swqe_polarity = !qp->swqe_polarity;
	wqe_ptr = (uintptr_t)qp->sq_base[*wqe_idx].elem;
	offset = (u16)(wqe_ptr) & 0x7F;
	if ((offset + wqe_size) > I40IW_QP_WQE_MAX_SIZE) {
		nop_wqe_cnt = (u8)(I40IW_QP_WQE_MAX_SIZE - offset) / I40IW_QP_WQE_MIN_SIZE;
		for (i = 0; i < nop_wqe_cnt; i++) {
			i40iw_nop_1(qp);
			I40IW_RING_MOVE_HEAD(qp->sq_ring, ret_code);
			if (ret_code)
				return NULL;
		}

		*wqe_idx = I40IW_RING_GETCURRENT_HEAD(qp->sq_ring);
		if (!*wqe_idx)
			qp->swqe_polarity = !qp->swqe_polarity;
	}

	if (((*wqe_idx & 3) == 1) && (wqe_size == I40IW_WQE_SIZE_64)) {
		i40iw_nop_1(qp);
		I40IW_RING_MOVE_HEAD(qp->sq_ring, ret_code);
		if (ret_code)
			return NULL;
		*wqe_idx = I40IW_RING_GETCURRENT_HEAD(qp->sq_ring);
		if (!*wqe_idx)
			qp->swqe_polarity = !qp->swqe_polarity;
	}
	I40IW_RING_MOVE_HEAD_BY_COUNT(qp->sq_ring,
				      wqe_size / I40IW_QP_WQE_MIN_SIZE, ret_code);
	if (ret_code)
		return NULL;

	wqe = qp->sq_base[*wqe_idx].elem;

	peek_head = I40IW_RING_GETCURRENT_HEAD(qp->sq_ring);
	wqe_0 = qp->sq_base[peek_head].elem;

	if (((peek_head & 3) == 1) || ((peek_head & 3) == 3)) {
		if (RS_64(wqe_0[3], I40IWQPSQ_VALID) != !qp->swqe_polarity)
			wqe_0[3] = LS_64(!qp->swqe_polarity, I40IWQPSQ_VALID);
	}

	qp->sq_wrtrk_array[*wqe_idx].wrid = wr_id;
	qp->sq_wrtrk_array[*wqe_idx].wr_len = total_size;
	qp->sq_wrtrk_array[*wqe_idx].wqe_size = wqe_size;
	return wqe;
}
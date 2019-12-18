#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct i40iw_qp_uk {int rwqe_polarity; int rq_wqe_size_multiplier; TYPE_1__* rq_base; int /*<<< orphan*/  rq_ring; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_2__ {int /*<<< orphan*/ * elem; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_ATOMIC_RING_MOVE_HEAD (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ I40IW_RING_FULL_ERR (int /*<<< orphan*/ ) ; 

u64 *i40iw_qp_get_next_recv_wqe(struct i40iw_qp_uk *qp, u32 *wqe_idx)
{
	u64 *wqe = NULL;
	enum i40iw_status_code ret_code;

	if (I40IW_RING_FULL_ERR(qp->rq_ring))
		return NULL;

	I40IW_ATOMIC_RING_MOVE_HEAD(qp->rq_ring, *wqe_idx, ret_code);
	if (ret_code)
		return NULL;
	if (!*wqe_idx)
		qp->rwqe_polarity = !qp->rwqe_polarity;
	/* rq_wqe_size_multiplier is no of qwords in one rq wqe */
	wqe = qp->rq_base[*wqe_idx * (qp->rq_wqe_size_multiplier >> 2)].elem;

	return wqe;
}
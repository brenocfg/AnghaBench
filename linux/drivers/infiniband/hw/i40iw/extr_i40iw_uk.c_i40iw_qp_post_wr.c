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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ head; } ;
struct TYPE_3__ {scalar_t__ head; } ;
struct i40iw_qp_uk {TYPE_2__ sq_ring; TYPE_1__ initial_ring; int /*<<< orphan*/  wqe_alloc_reg; int /*<<< orphan*/  qp_id; int /*<<< orphan*/  shadow_area; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_QP_DBSA_HW_SQ_TAIL ; 
 scalar_t__ I40IW_RING_GETCURRENT_HEAD (TYPE_2__) ; 
 scalar_t__ RS_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_64bit_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void i40iw_qp_post_wr(struct i40iw_qp_uk *qp)
{
	u64 temp;
	u32 hw_sq_tail;
	u32 sw_sq_head;

	mb(); /* valid bit is written and loads completed before reading shadow */

	/* read the doorbell shadow area */
	get_64bit_val(qp->shadow_area, 0, &temp);

	hw_sq_tail = (u32)RS_64(temp, I40IW_QP_DBSA_HW_SQ_TAIL);
	sw_sq_head = I40IW_RING_GETCURRENT_HEAD(qp->sq_ring);
	if (sw_sq_head != hw_sq_tail) {
		if (sw_sq_head > qp->initial_ring.head) {
			if ((hw_sq_tail >= qp->initial_ring.head) &&
			    (hw_sq_tail < sw_sq_head)) {
				writel(qp->qp_id, qp->wqe_alloc_reg);
			}
		} else if (sw_sq_head != qp->initial_ring.head) {
			if ((hw_sq_tail >= qp->initial_ring.head) ||
			    (hw_sq_tail < sw_sq_head)) {
				writel(qp->qp_id, qp->wqe_alloc_reg);
			}
		}
	}

	qp->initial_ring.head = qp->sq_ring.head;
}
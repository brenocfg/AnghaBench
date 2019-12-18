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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  head; } ;
struct i40iw_qp_uk {int qp_id; int /*<<< orphan*/  sq_ring; TYPE_1__ initial_ring; int /*<<< orphan*/  push_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_PFPE_WQEALLOC_WQE_DESC_INDEX ; 
 int /*<<< orphan*/  I40IW_RING_GETCURRENT_HEAD (int /*<<< orphan*/ ) ; 
 int LS_32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_32bit_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void i40iw_qp_ring_push_db(struct i40iw_qp_uk *qp, u32 wqe_idx)
{
	set_32bit_val(qp->push_db, 0, LS_32((wqe_idx >> 2), I40E_PFPE_WQEALLOC_WQE_DESC_INDEX) | qp->qp_id);
	qp->initial_ring.head = I40IW_RING_GETCURRENT_HEAD(qp->sq_ring);
}
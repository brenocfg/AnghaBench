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
typedef  int u16 ;
struct fcoe_sqe {int wqe; } ;
struct bnx2fc_rport {size_t sq_prod_idx; int sq_curr_toggle_bit; struct fcoe_sqe* sq; } ;

/* Variables and functions */
 size_t BNX2FC_SQ_WQES_MAX ; 
 int FCOE_SQE_TASK_ID_SHIFT ; 
 int FCOE_SQE_TOGGLE_BIT_SHIFT ; 

void bnx2fc_add_2_sq(struct bnx2fc_rport *tgt, u16 xid)
{
	struct fcoe_sqe *sqe;

	sqe = &tgt->sq[tgt->sq_prod_idx];

	/* Fill SQ WQE */
	sqe->wqe = xid << FCOE_SQE_TASK_ID_SHIFT;
	sqe->wqe |= tgt->sq_curr_toggle_bit << FCOE_SQE_TOGGLE_BIT_SHIFT;

	/* Advance SQ Prod Idx */
	if (++tgt->sq_prod_idx == BNX2FC_SQ_WQES_MAX) {
		tgt->sq_prod_idx = 0;
		tgt->sq_curr_toggle_bit = 1 - tgt->sq_curr_toggle_bit;
	}
}
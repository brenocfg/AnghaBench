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
typedef  int /*<<< orphan*/  u32 ;
struct i40iw_qp_uk {int swqe_polarity; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40IWQPSQ_OPCODE ; 
 int /*<<< orphan*/  I40IWQPSQ_SIGCOMPL ; 
 int /*<<< orphan*/  I40IWQPSQ_VALID ; 
 int I40IWQP_OP_NOP ; 
 int I40IW_ERR_QP_TOOMANY_WRS_POSTED ; 
 int /*<<< orphan*/  I40IW_QP_WQE_MIN_SIZE ; 
 int LS_64 (int,int /*<<< orphan*/ ) ; 
 int* i40iw_qp_get_next_send_wqe (struct i40iw_qp_uk*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i40iw_qp_post_wr (struct i40iw_qp_uk*) ; 
 int /*<<< orphan*/  set_64bit_val (int*,int,int) ; 
 int /*<<< orphan*/  wmb () ; 

enum i40iw_status_code i40iw_nop(struct i40iw_qp_uk *qp,
				 u64 wr_id,
				 bool signaled,
				 bool post_sq)
{
	u64 header, *wqe;
	u32 wqe_idx;

	wqe = i40iw_qp_get_next_send_wqe(qp, &wqe_idx, I40IW_QP_WQE_MIN_SIZE, 0, wr_id);
	if (!wqe)
		return I40IW_ERR_QP_TOOMANY_WRS_POSTED;
	set_64bit_val(wqe, 0, 0);
	set_64bit_val(wqe, 8, 0);
	set_64bit_val(wqe, 16, 0);

	header = LS_64(I40IWQP_OP_NOP, I40IWQPSQ_OPCODE) |
	    LS_64(signaled, I40IWQPSQ_SIGCOMPL) |
	    LS_64(qp->swqe_polarity, I40IWQPSQ_VALID);

	wmb(); /* make sure WQE is populated before valid bit is set */

	set_64bit_val(wqe, 24, header);
	if (post_sq)
		i40iw_qp_post_wr(qp);

	return 0;
}
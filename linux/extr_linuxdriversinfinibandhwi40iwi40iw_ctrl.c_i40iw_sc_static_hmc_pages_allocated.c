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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct i40iw_sc_cqp {int /*<<< orphan*/  dev; int /*<<< orphan*/  polarity; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_CQPSQ_OPCODE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_WQEVALID ; 
 int /*<<< orphan*/  I40IW_CQP_OP_SHMC_PAGES_ALLOCATED ; 
 int I40IW_CQP_WQE_SIZE ; 
 int /*<<< orphan*/  I40IW_DEBUG_WQE ; 
 int I40IW_ERR_CQP_COMPL_ERROR ; 
 int I40IW_ERR_RING_FULL ; 
 int /*<<< orphan*/  I40IW_SHMC_PAGE_ALLOCATED_HMC_FN_ID ; 
 int LS_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i40iw_cqp_poll_registers (struct i40iw_sc_cqp*,scalar_t__,int) ; 
 int /*<<< orphan*/  i40iw_debug_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  i40iw_get_cqp_reg_info (struct i40iw_sc_cqp*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  i40iw_insert_wqe_hdr (int*,int) ; 
 int* i40iw_sc_cqp_get_next_send_wqe (struct i40iw_sc_cqp*,int) ; 
 int /*<<< orphan*/  i40iw_sc_cqp_post_sq (struct i40iw_sc_cqp*) ; 
 int i40iw_sc_poll_for_cqp_op_done (struct i40iw_sc_cqp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_64bit_val (int*,int,int) ; 

enum i40iw_status_code i40iw_sc_static_hmc_pages_allocated(
					struct i40iw_sc_cqp *cqp,
					u64 scratch,
					u8 hmc_fn_id,
					bool post_sq,
					bool poll_registers)
{
	u64 header;
	u64 *wqe;
	u32 tail, val, error;
	enum i40iw_status_code ret_code = 0;

	wqe = i40iw_sc_cqp_get_next_send_wqe(cqp, scratch);
	if (!wqe)
		return I40IW_ERR_RING_FULL;
	set_64bit_val(wqe,
		      16,
		      LS_64(hmc_fn_id, I40IW_SHMC_PAGE_ALLOCATED_HMC_FN_ID));

	header = LS_64(I40IW_CQP_OP_SHMC_PAGES_ALLOCATED, I40IW_CQPSQ_OPCODE) |
		 LS_64(cqp->polarity, I40IW_CQPSQ_WQEVALID);

	i40iw_insert_wqe_hdr(wqe, header);

	i40iw_debug_buf(cqp->dev, I40IW_DEBUG_WQE, "SHMC_PAGES_ALLOCATED WQE",
			wqe, I40IW_CQP_WQE_SIZE * 8);
	i40iw_get_cqp_reg_info(cqp, &val, &tail, &error);
	if (error) {
		ret_code = I40IW_ERR_CQP_COMPL_ERROR;
		return ret_code;
	}
	if (post_sq) {
		i40iw_sc_cqp_post_sq(cqp);
		if (poll_registers)
			/* check for cqp sq tail update */
			ret_code = i40iw_cqp_poll_registers(cqp, tail, 1000);
		else
			ret_code = i40iw_sc_poll_for_cqp_op_done(cqp,
								 I40IW_CQP_OP_SHMC_PAGES_ALLOCATED,
								 NULL);
	}

	return ret_code;
}
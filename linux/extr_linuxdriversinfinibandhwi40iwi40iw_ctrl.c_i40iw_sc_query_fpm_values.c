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
typedef  scalar_t__ u8 ;
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct i40iw_sc_cqp {int /*<<< orphan*/  dev; int /*<<< orphan*/  polarity; } ;
struct i40iw_dma_mem {scalar_t__ pa; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_CQPSQ_OPCODE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_WQEVALID ; 
 int /*<<< orphan*/  I40IW_CQP_OP_QUERY_FPM_VALUES ; 
 scalar_t__ I40IW_CQP_WAIT_POLL_CQ ; 
 scalar_t__ I40IW_CQP_WAIT_POLL_REGS ; 
 int I40IW_CQP_WQE_SIZE ; 
 int /*<<< orphan*/  I40IW_DEBUG_WQE ; 
 int /*<<< orphan*/  I40IW_DONE_COUNT ; 
 int I40IW_ERR_CQP_COMPL_ERROR ; 
 int I40IW_ERR_RING_FULL ; 
 int LS_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i40iw_cqp_poll_registers (struct i40iw_sc_cqp*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_debug_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  i40iw_get_cqp_reg_info (struct i40iw_sc_cqp*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  i40iw_insert_wqe_hdr (int*,int) ; 
 int* i40iw_sc_cqp_get_next_send_wqe (struct i40iw_sc_cqp*,int) ; 
 int /*<<< orphan*/  i40iw_sc_cqp_post_sq (struct i40iw_sc_cqp*) ; 
 int i40iw_sc_query_fpm_values_done (struct i40iw_sc_cqp*) ; 
 int /*<<< orphan*/  set_64bit_val (int*,int,scalar_t__) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_sc_query_fpm_values(
					struct i40iw_sc_cqp *cqp,
					u64 scratch,
					u8 hmc_fn_id,
					struct i40iw_dma_mem *query_fpm_mem,
					bool post_sq,
					u8 wait_type)
{
	u64 *wqe;
	u64 header;
	u32 tail, val, error;
	enum i40iw_status_code ret_code = 0;

	wqe = i40iw_sc_cqp_get_next_send_wqe(cqp, scratch);
	if (!wqe)
		return I40IW_ERR_RING_FULL;

	set_64bit_val(wqe, 16, hmc_fn_id);
	set_64bit_val(wqe, 32, query_fpm_mem->pa);

	header = LS_64(I40IW_CQP_OP_QUERY_FPM_VALUES, I40IW_CQPSQ_OPCODE) |
		 LS_64(cqp->polarity, I40IW_CQPSQ_WQEVALID);

	i40iw_insert_wqe_hdr(wqe, header);

	i40iw_debug_buf(cqp->dev, I40IW_DEBUG_WQE, "QUERY_FPM WQE",
			wqe, I40IW_CQP_WQE_SIZE * 8);

	/* read the tail from CQP_TAIL register */
	i40iw_get_cqp_reg_info(cqp, &val, &tail, &error);

	if (error)
		return I40IW_ERR_CQP_COMPL_ERROR;

	if (post_sq) {
		i40iw_sc_cqp_post_sq(cqp);
		if (wait_type == I40IW_CQP_WAIT_POLL_REGS)
			ret_code = i40iw_cqp_poll_registers(cqp, tail, I40IW_DONE_COUNT);
		else if (wait_type == I40IW_CQP_WAIT_POLL_CQ)
			ret_code = i40iw_sc_query_fpm_values_done(cqp);
	}

	return ret_code;
}
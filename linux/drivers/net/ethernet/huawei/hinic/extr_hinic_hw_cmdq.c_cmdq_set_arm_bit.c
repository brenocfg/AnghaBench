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
typedef  scalar_t__ u16 ;
struct hinic_wq {int wqebb_size; scalar_t__ q_depth; } ;
struct hinic_cmdq_wqe {int dummy; } ;
struct hinic_hw_wqe {struct hinic_cmdq_wqe cmdq_wqe; } ;
struct hinic_cmdq {int wrapped; int /*<<< orphan*/  cmdq_lock; struct hinic_wq* wq; } ;

/* Variables and functions */
 int ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CMDQ_CMD_SYNC_DIRECT_RESP ; 
 int /*<<< orphan*/  CMDQ_SET_ARM_CMD ; 
 int EBUSY ; 
 int /*<<< orphan*/  HINIC_CMDQ_SYNC ; 
 int /*<<< orphan*/  HINIC_CMD_ACK_TYPE_CMDQ ; 
 int /*<<< orphan*/  HINIC_MOD_COMM ; 
 scalar_t__ IS_ERR (struct hinic_hw_wqe*) ; 
 int /*<<< orphan*/  WQE_SCMD_SIZE ; 
 int /*<<< orphan*/  cmdq_set_db (struct hinic_cmdq*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cmdq_set_direct_wqe (struct hinic_cmdq_wqe*,int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cmdq_wqe_fill (struct hinic_cmdq_wqe*,struct hinic_cmdq_wqe*) ; 
 int /*<<< orphan*/  hinic_cpu_to_be32 (struct hinic_cmdq_wqe*,int /*<<< orphan*/ ) ; 
 struct hinic_hw_wqe* hinic_get_wqe (struct hinic_wq*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmdq_set_arm_bit(struct hinic_cmdq *cmdq, void *buf_in,
			    u16 in_size)
{
	struct hinic_cmdq_wqe *curr_cmdq_wqe, cmdq_wqe;
	u16 curr_prod_idx, next_prod_idx;
	struct hinic_wq *wq = cmdq->wq;
	struct hinic_hw_wqe *hw_wqe;
	int wrapped, num_wqebbs;

	/* Keep doorbell index correct */
	spin_lock(&cmdq->cmdq_lock);

	/* WQE_SIZE = WQEBB_SIZE, we will get the wq element and not shadow*/
	hw_wqe = hinic_get_wqe(wq, WQE_SCMD_SIZE, &curr_prod_idx);
	if (IS_ERR(hw_wqe)) {
		spin_unlock(&cmdq->cmdq_lock);
		return -EBUSY;
	}

	curr_cmdq_wqe = &hw_wqe->cmdq_wqe;

	wrapped = cmdq->wrapped;

	num_wqebbs = ALIGN(WQE_SCMD_SIZE, wq->wqebb_size) / wq->wqebb_size;
	next_prod_idx = curr_prod_idx + num_wqebbs;
	if (next_prod_idx >= wq->q_depth) {
		cmdq->wrapped = !cmdq->wrapped;
		next_prod_idx -= wq->q_depth;
	}

	cmdq_set_direct_wqe(&cmdq_wqe, CMDQ_CMD_SYNC_DIRECT_RESP, buf_in,
			    in_size, NULL, wrapped, HINIC_CMD_ACK_TYPE_CMDQ,
			    HINIC_MOD_COMM, CMDQ_SET_ARM_CMD, curr_prod_idx);

	/* The data that is written to HW should be in Big Endian Format */
	hinic_cpu_to_be32(&cmdq_wqe, WQE_SCMD_SIZE);

	/* cmdq wqe is not shadow, therefore wqe will be written to wq */
	cmdq_wqe_fill(curr_cmdq_wqe, &cmdq_wqe);

	cmdq_set_db(cmdq, HINIC_CMDQ_SYNC, next_prod_idx);

	spin_unlock(&cmdq->cmdq_lock);
	return 0;
}
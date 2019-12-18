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
typedef  int /*<<< orphan*/  u32 ;
struct hinic_ctrl {int /*<<< orphan*/  ctrl_info; } ;
struct hinic_cmdq_wqe_scmd {struct hinic_ctrl ctrl; } ;
struct hinic_cmdq_direct_wqe {struct hinic_cmdq_wqe_scmd wqe_scmd; } ;
struct hinic_cmdq_wqe {struct hinic_cmdq_direct_wqe direct_wqe; } ;
struct hinic_cmdq {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDQ_WQE_COMPLETED (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  WQE_SCMD_SIZE ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_wqe_complete_bit (struct hinic_cmdq*,struct hinic_cmdq_wqe*) ; 
 int /*<<< orphan*/  hinic_put_wqe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmdq_arm_ceq_handler(struct hinic_cmdq *cmdq,
				struct hinic_cmdq_wqe *wqe)
{
	struct hinic_cmdq_direct_wqe *direct_wqe = &wqe->direct_wqe;
	struct hinic_cmdq_wqe_scmd *wqe_scmd;
	struct hinic_ctrl *ctrl;
	u32 ctrl_info;

	wqe_scmd = &direct_wqe->wqe_scmd;
	ctrl = &wqe_scmd->ctrl;
	ctrl_info = be32_to_cpu(ctrl->ctrl_info);

	/* HW should toggle the HW BUSY BIT */
	if (!CMDQ_WQE_COMPLETED(ctrl_info))
		return -EBUSY;

	clear_wqe_complete_bit(cmdq, wqe);

	hinic_put_wqe(cmdq->wq, WQE_SCMD_SIZE);
	return 0;
}
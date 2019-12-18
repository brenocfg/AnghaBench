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
typedef  int /*<<< orphan*/  u16 ;
struct hinic_status {int /*<<< orphan*/  status_info; } ;
struct hinic_ctrl {int /*<<< orphan*/  ctrl_info; } ;
struct hinic_cmdq_wqe_lcmd {struct hinic_ctrl ctrl; struct hinic_status status; } ;
struct hinic_cmdq_wqe {struct hinic_cmdq_wqe_lcmd wqe_lcmd; } ;
struct hinic_cmdq {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDQ_WQE_COMPLETED (int /*<<< orphan*/ ) ; 
 int CMDQ_WQE_ERRCODE_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  VAL ; 
 int /*<<< orphan*/  WQE_LCMD_SIZE ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_wqe_complete_bit (struct hinic_cmdq*,struct hinic_cmdq_wqe*) ; 
 int /*<<< orphan*/  cmdq_sync_cmd_handler (struct hinic_cmdq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hinic_put_wqe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmdq_cmd_ceq_handler(struct hinic_cmdq *cmdq, u16 ci,
				struct hinic_cmdq_wqe *cmdq_wqe)
{
	struct hinic_cmdq_wqe_lcmd *wqe_lcmd = &cmdq_wqe->wqe_lcmd;
	struct hinic_status *status = &wqe_lcmd->status;
	struct hinic_ctrl *ctrl = &wqe_lcmd->ctrl;
	int errcode;

	if (!CMDQ_WQE_COMPLETED(be32_to_cpu(ctrl->ctrl_info)))
		return -EBUSY;

	errcode = CMDQ_WQE_ERRCODE_GET(be32_to_cpu(status->status_info), VAL);

	cmdq_sync_cmd_handler(cmdq, ci, errcode);

	clear_wqe_complete_bit(cmdq, cmdq_wqe);
	hinic_put_wqe(cmdq->wq, WQE_LCMD_SIZE);
	return 0;
}
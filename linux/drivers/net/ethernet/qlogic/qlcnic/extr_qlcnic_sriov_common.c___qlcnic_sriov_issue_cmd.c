#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct qlcnic_mailbox {int /*<<< orphan*/  status; } ;
struct qlcnic_hardware_context {int reset_context; int /*<<< orphan*/  pci_func; TYPE_3__* sriov; struct qlcnic_mailbox* mailbox; } ;
struct TYPE_12__ {int* arg; } ;
struct TYPE_11__ {int* arg; } ;
struct qlcnic_cmd_args {scalar_t__ type; TYPE_6__ req; TYPE_5__ rsp; } ;
struct qlcnic_bc_trans {TYPE_4__* req_hdr; } ;
struct qlcnic_adapter {int need_fw_reset; struct qlcnic_hardware_context* ahw; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_10__ {scalar_t__ cmd_op; } ;
struct TYPE_8__ {int /*<<< orphan*/  trans_counter; } ;
struct TYPE_9__ {TYPE_2__ bc; } ;
struct TYPE_7__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int EIO ; 
 int /*<<< orphan*/  QLCDB (struct qlcnic_adapter*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ QLCNIC_BC_CMD_CHANNEL_INIT ; 
 int QLCNIC_MBX_PORT_RSP_OK ; 
 int QLCNIC_MBX_RSP (int) ; 
 int QLCNIC_MBX_RSP_OK ; 
 int QLCNIC_MBX_STATUS (int) ; 
 int QLCNIC_RCODE_SUCCESS ; 
 int QLCNIC_RCODE_TIMEOUT ; 
 scalar_t__ QLC_83XX_MBX_CMD_NO_WAIT ; 
 int /*<<< orphan*/  QLC_83XX_MBX_READY ; 
 int /*<<< orphan*/  QLC_BC_COMMAND ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int,...) ; 
 int /*<<< orphan*/  kfree (struct qlcnic_cmd_args*) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_sriov_alloc_bc_trans (struct qlcnic_bc_trans**) ; 
 int /*<<< orphan*/  qlcnic_sriov_cleanup_transaction (struct qlcnic_bc_trans*) ; 
 int qlcnic_sriov_prepare_bc_hdr (struct qlcnic_bc_trans*,struct qlcnic_cmd_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_sriov_retry_bc_cmd (struct qlcnic_adapter*,struct qlcnic_bc_trans*) ; 
 int qlcnic_sriov_send_bc_cmd (struct qlcnic_adapter*,struct qlcnic_bc_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __qlcnic_sriov_issue_cmd(struct qlcnic_adapter *adapter,
				  struct qlcnic_cmd_args *cmd)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	struct qlcnic_mailbox *mbx = ahw->mailbox;
	struct device *dev = &adapter->pdev->dev;
	struct qlcnic_bc_trans *trans;
	int err;
	u32 rsp_data, opcode, mbx_err_code, rsp;
	u16 seq = ++adapter->ahw->sriov->bc.trans_counter;
	u8 func = ahw->pci_func;

	rsp = qlcnic_sriov_alloc_bc_trans(&trans);
	if (rsp)
		goto free_cmd;

	rsp = qlcnic_sriov_prepare_bc_hdr(trans, cmd, seq, QLC_BC_COMMAND);
	if (rsp)
		goto cleanup_transaction;

retry:
	if (!test_bit(QLC_83XX_MBX_READY, &mbx->status)) {
		rsp = -EIO;
		QLCDB(adapter, DRV, "MBX not Ready!(cmd 0x%x) for VF 0x%x\n",
		      QLCNIC_MBX_RSP(cmd->req.arg[0]), func);
		goto err_out;
	}

	err = qlcnic_sriov_send_bc_cmd(adapter, trans, func);
	if (err) {
		dev_err(dev, "MBX command 0x%x timed out for VF %d\n",
			(cmd->req.arg[0] & 0xffff), func);
		rsp = QLCNIC_RCODE_TIMEOUT;

		/* After adapter reset PF driver may take some time to
		 * respond to VF's request. Retry request till maximum retries.
		 */
		if ((trans->req_hdr->cmd_op == QLCNIC_BC_CMD_CHANNEL_INIT) &&
		    !qlcnic_sriov_retry_bc_cmd(adapter, trans))
			goto retry;

		goto err_out;
	}

	rsp_data = cmd->rsp.arg[0];
	mbx_err_code = QLCNIC_MBX_STATUS(rsp_data);
	opcode = QLCNIC_MBX_RSP(cmd->req.arg[0]);

	if ((mbx_err_code == QLCNIC_MBX_RSP_OK) ||
	    (mbx_err_code == QLCNIC_MBX_PORT_RSP_OK)) {
		rsp = QLCNIC_RCODE_SUCCESS;
	} else {
		if (cmd->type == QLC_83XX_MBX_CMD_NO_WAIT) {
			rsp = QLCNIC_RCODE_SUCCESS;
		} else {
			rsp = mbx_err_code;
			if (!rsp)
				rsp = 1;

			dev_err(dev,
				"MBX command 0x%x failed with err:0x%x for VF %d\n",
				opcode, mbx_err_code, func);
		}
	}

err_out:
	if (rsp == QLCNIC_RCODE_TIMEOUT) {
		ahw->reset_context = 1;
		adapter->need_fw_reset = 1;
		clear_bit(QLC_83XX_MBX_READY, &mbx->status);
	}

cleanup_transaction:
	qlcnic_sriov_cleanup_transaction(trans);

free_cmd:
	if (cmd->type == QLC_83XX_MBX_CMD_NO_WAIT) {
		qlcnic_free_mbx_args(cmd);
		kfree(cmd);
	}

	return rsp;
}
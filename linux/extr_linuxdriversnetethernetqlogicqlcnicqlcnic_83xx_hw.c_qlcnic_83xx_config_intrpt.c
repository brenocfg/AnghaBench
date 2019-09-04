#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_8__ {int* arg; } ;
struct TYPE_6__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_3__ rsp; TYPE_1__ req; } ;
struct qlcnic_adapter {TYPE_5__* ahw; TYPE_2__* pdev; } ;
struct TYPE_10__ {int num_msix; int pci_func; TYPE_4__* intr_tbl; } ;
struct TYPE_9__ {int type; int id; int enabled; int src; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT_16 ; 
 scalar_t__ LSB (int) ; 
 int MSW (int) ; 
 int /*<<< orphan*/  QLCNIC_CMD_CONFIG_INTRPT ; 
 int QLCNIC_INTRPT_ADD ; 
 int QLCNIC_INTRPT_DEL ; 
 int QLCNIC_INTRPT_MSIX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 
 scalar_t__ qlcnic_sriov_vf_check (struct qlcnic_adapter*) ; 

int qlcnic_83xx_config_intrpt(struct qlcnic_adapter *adapter, bool op_type)
{
	int i, index, err;
	u8 max_ints;
	u32 val, temp, type;
	struct qlcnic_cmd_args cmd;

	max_ints = adapter->ahw->num_msix - 1;
	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_CONFIG_INTRPT);
	if (err)
		return err;

	cmd.req.arg[1] = max_ints;

	if (qlcnic_sriov_vf_check(adapter))
		cmd.req.arg[1] |= (adapter->ahw->pci_func << 8) | BIT_16;

	for (i = 0, index = 2; i < max_ints; i++) {
		type = op_type ? QLCNIC_INTRPT_ADD : QLCNIC_INTRPT_DEL;
		val = type | (adapter->ahw->intr_tbl[i].type << 4);
		if (adapter->ahw->intr_tbl[i].type == QLCNIC_INTRPT_MSIX)
			val |= (adapter->ahw->intr_tbl[i].id << 16);
		cmd.req.arg[index++] = val;
	}
	err = qlcnic_issue_cmd(adapter, &cmd);
	if (err) {
		dev_err(&adapter->pdev->dev,
			"Failed to configure interrupts 0x%x\n", err);
		goto out;
	}

	max_ints = cmd.rsp.arg[1];
	for (i = 0, index = 2; i < max_ints; i++, index += 2) {
		val = cmd.rsp.arg[index];
		if (LSB(val)) {
			dev_info(&adapter->pdev->dev,
				 "Can't configure interrupt %d\n",
				 adapter->ahw->intr_tbl[i].id);
			continue;
		}
		if (op_type) {
			adapter->ahw->intr_tbl[i].id = MSW(val);
			adapter->ahw->intr_tbl[i].enabled = 1;
			temp = cmd.rsp.arg[index + 1];
			adapter->ahw->intr_tbl[i].src = temp;
		} else {
			adapter->ahw->intr_tbl[i].id = i;
			adapter->ahw->intr_tbl[i].enabled = 0;
			adapter->ahw->intr_tbl[i].src = 0;
		}
	}
out:
	qlcnic_free_mbx_args(&cmd);
	return err;
}
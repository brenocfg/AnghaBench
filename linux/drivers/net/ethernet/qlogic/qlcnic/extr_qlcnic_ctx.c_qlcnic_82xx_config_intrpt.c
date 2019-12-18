#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct qlcnic_hardware_context {int num_msix; TYPE_3__* intr_tbl; } ;
struct TYPE_5__ {int* arg; } ;
struct TYPE_4__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_2__ rsp; TYPE_1__ req; } ;
struct qlcnic_adapter {struct net_device* netdev; struct qlcnic_hardware_context* ahw; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int type; int id; int enabled; int src; } ;

/* Variables and functions */
 scalar_t__ LSB (int) ; 
 int MSW (int) ; 
 int /*<<< orphan*/  QLCNIC_CMD_MQ_TX_CONFIG_INTR ; 
 scalar_t__ QLCNIC_INTRPT_ADD ; 
 scalar_t__ QLCNIC_INTRPT_DEL ; 
 int QLCNIC_INTRPT_MSIX ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,char*,int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int) ; 
 int qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 

int qlcnic_82xx_config_intrpt(struct qlcnic_adapter *adapter, u8 op_type)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	struct net_device *netdev = adapter->netdev;
	struct qlcnic_cmd_args cmd;
	u32 type, val;
	int i, err = 0;

	for (i = 0; i < ahw->num_msix; i++) {
		err = qlcnic_alloc_mbx_args(&cmd, adapter,
					    QLCNIC_CMD_MQ_TX_CONFIG_INTR);
		if (err)
			return err;
		type = op_type ? QLCNIC_INTRPT_ADD : QLCNIC_INTRPT_DEL;
		val = type | (ahw->intr_tbl[i].type << 4);
		if (ahw->intr_tbl[i].type == QLCNIC_INTRPT_MSIX)
			val |= (ahw->intr_tbl[i].id << 16);
		cmd.req.arg[1] = val;
		err = qlcnic_issue_cmd(adapter, &cmd);
		if (err) {
			netdev_err(netdev, "Failed to %s interrupts %d\n",
				   op_type == QLCNIC_INTRPT_ADD ? "Add" :
				   "Delete", err);
			qlcnic_free_mbx_args(&cmd);
			return err;
		}
		val = cmd.rsp.arg[1];
		if (LSB(val)) {
			netdev_info(netdev,
				    "failed to configure interrupt for %d\n",
				    ahw->intr_tbl[i].id);
			continue;
		}
		if (op_type) {
			ahw->intr_tbl[i].id = MSW(val);
			ahw->intr_tbl[i].enabled = 1;
			ahw->intr_tbl[i].src = cmd.rsp.arg[2];
		} else {
			ahw->intr_tbl[i].id = i;
			ahw->intr_tbl[i].enabled = 0;
			ahw->intr_tbl[i].src = 0;
		}
		qlcnic_free_mbx_args(&cmd);
	}

	return err;
}
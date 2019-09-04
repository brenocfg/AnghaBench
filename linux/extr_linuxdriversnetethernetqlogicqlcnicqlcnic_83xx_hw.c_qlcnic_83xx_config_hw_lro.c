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
typedef  int u32 ;
struct TYPE_5__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_2__ req; } ;
struct qlcnic_adapter {TYPE_3__* pdev; TYPE_1__* recv_ctx; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ state; int context_id; } ;

/* Variables and functions */
 int BIT_0 ; 
 int BIT_1 ; 
 int BIT_2 ; 
 int BIT_3 ; 
 int /*<<< orphan*/  QLCNIC_CMD_CONFIGURE_HW_LRO ; 
 scalar_t__ QLCNIC_HOST_CTX_STATE_FREED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 

int qlcnic_83xx_config_hw_lro(struct qlcnic_adapter *adapter, int mode)
{
	int err;
	u32 temp, arg1;
	struct qlcnic_cmd_args cmd;
	int lro_bit_mask;

	lro_bit_mask = (mode ? (BIT_0 | BIT_1 | BIT_2 | BIT_3) : 0);

	if (adapter->recv_ctx->state == QLCNIC_HOST_CTX_STATE_FREED)
		return 0;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_CONFIGURE_HW_LRO);
	if (err)
		return err;

	temp = adapter->recv_ctx->context_id << 16;
	arg1 = lro_bit_mask | temp;
	cmd.req.arg[1] = arg1;

	err = qlcnic_issue_cmd(adapter, &cmd);
	if (err)
		dev_info(&adapter->pdev->dev, "LRO config failed\n");
	qlcnic_free_mbx_args(&cmd);

	return err;
}
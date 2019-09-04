#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_3__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_1__ req; } ;
struct qlcnic_adapter {TYPE_2__* pdev; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  QLCNIC_CMD_BC_EVENT_SETUP ; 
 int QLCNIC_RCODE_SUCCESS ; 
 int /*<<< orphan*/  __QLCNIC_SRIOV_ENABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*,int) ; 
 int qlcnic_83xx_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 
 scalar_t__ qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qlcnic_sriov_cfg_bc_intr(struct qlcnic_adapter *adapter, u8 enable)
{
	struct qlcnic_cmd_args cmd;
	int err;

	if (!test_bit(__QLCNIC_SRIOV_ENABLE, &adapter->state))
		return 0;

	if (qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_BC_EVENT_SETUP))
		return -ENOMEM;

	if (enable)
		cmd.req.arg[1] = (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);

	err = qlcnic_83xx_issue_cmd(adapter, &cmd);

	if (err != QLCNIC_RCODE_SUCCESS) {
		dev_err(&adapter->pdev->dev,
			"Failed to %s bc events, err=%d\n",
			(enable ? "enable" : "disable"), err);
	}

	qlcnic_free_mbx_args(&cmd);
	return err;
}
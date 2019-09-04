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
struct TYPE_4__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_2__ req; } ;
struct qlcnic_adapter {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int QLCNIC_83XX_ADD_PORT0 ; 
 int QLCNIC_83XX_ADD_PORT1 ; 
 void* QLCNIC_83XX_EXTENDED_MEM_SIZE ; 
 int /*<<< orphan*/  QLCNIC_CMD_83XX_EXTEND_ISCSI_DUMP_CAP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 

int qlcnic_83xx_extend_md_capab(struct qlcnic_adapter *adapter)
{
	struct qlcnic_cmd_args cmd;
	int err;

	err = qlcnic_alloc_mbx_args(&cmd, adapter,
				    QLCNIC_CMD_83XX_EXTEND_ISCSI_DUMP_CAP);
	if (err)
		return err;

	cmd.req.arg[1] = (QLCNIC_83XX_ADD_PORT0 | QLCNIC_83XX_ADD_PORT1);
	cmd.req.arg[2] = QLCNIC_83XX_EXTENDED_MEM_SIZE;
	cmd.req.arg[3] = QLCNIC_83XX_EXTENDED_MEM_SIZE;

	err = qlcnic_issue_cmd(adapter, &cmd);
	if (err)
		dev_err(&adapter->pdev->dev,
			"failed to issue extend iSCSI minidump capability\n");

	return err;
}
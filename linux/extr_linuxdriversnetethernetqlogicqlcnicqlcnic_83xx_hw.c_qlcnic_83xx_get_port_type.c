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
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_hardware_context {int /*<<< orphan*/  port_type; } ;
struct TYPE_3__ {int /*<<< orphan*/ * arg; } ;
struct qlcnic_cmd_args {TYPE_1__ rsp; } ;
struct qlcnic_adapter {TYPE_2__* pdev; struct qlcnic_hardware_context* ahw; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_CMD_GET_LINK_STATUS ; 
 int /*<<< orphan*/  QLCNIC_GBE ; 
 int /*<<< orphan*/  QLCNIC_XGBE ; 
#define  QLC_83XX_MODULE_FIBRE_1000BASE_CX 131 
#define  QLC_83XX_MODULE_FIBRE_1000BASE_LX 130 
#define  QLC_83XX_MODULE_FIBRE_1000BASE_SX 129 
#define  QLC_83XX_MODULE_TP_1000BASE_T 128 
 int QLC_83XX_SFP_MODULE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 

void qlcnic_83xx_get_port_type(struct qlcnic_adapter *adapter)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	struct qlcnic_cmd_args cmd;
	u32 config;
	int err;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_LINK_STATUS);
	if (err)
		return;

	err = qlcnic_issue_cmd(adapter, &cmd);
	if (err) {
		dev_info(&adapter->pdev->dev,
			 "Get Link Status Command failed: 0x%x\n", err);
		goto out;
	} else {
		config = cmd.rsp.arg[3];

		switch (QLC_83XX_SFP_MODULE_TYPE(config)) {
		case QLC_83XX_MODULE_FIBRE_1000BASE_SX:
		case QLC_83XX_MODULE_FIBRE_1000BASE_LX:
		case QLC_83XX_MODULE_FIBRE_1000BASE_CX:
		case QLC_83XX_MODULE_TP_1000BASE_T:
			ahw->port_type = QLCNIC_GBE;
			break;
		default:
			ahw->port_type = QLCNIC_XGBE;
		}
	}
out:
	qlcnic_free_mbx_args(&cmd);
}
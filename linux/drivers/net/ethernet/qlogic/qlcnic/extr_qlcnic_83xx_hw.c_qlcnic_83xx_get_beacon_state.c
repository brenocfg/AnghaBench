#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct qlcnic_hardware_context {int /*<<< orphan*/  beacon_state; } ;
struct TYPE_2__ {scalar_t__* arg; } ;
struct qlcnic_cmd_args {TYPE_1__ rsp; } ;
struct qlcnic_adapter {int /*<<< orphan*/  netdev; struct qlcnic_hardware_context* ahw; } ;

/* Variables and functions */
 scalar_t__ QLCNIC_BEACON_DISABLE ; 
 int /*<<< orphan*/  QLCNIC_CMD_GET_LED_CONFIG ; 
 int /*<<< orphan*/  QLC_83XX_BEACON_OFF ; 
 int /*<<< orphan*/  QLC_83XX_BEACON_ON ; 
 scalar_t__ QLC_83XX_ENABLE_BEACON ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 

__attribute__((used)) static void qlcnic_83xx_get_beacon_state(struct qlcnic_adapter *adapter)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	struct qlcnic_cmd_args cmd;
	u8 beacon_state;
	int err = 0;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_LED_CONFIG);
	if (!err) {
		err = qlcnic_issue_cmd(adapter, &cmd);
		if (!err) {
			beacon_state = cmd.rsp.arg[4];
			if (beacon_state == QLCNIC_BEACON_DISABLE)
				ahw->beacon_state = QLC_83XX_BEACON_OFF;
			else if (beacon_state == QLC_83XX_ENABLE_BEACON)
				ahw->beacon_state = QLC_83XX_BEACON_ON;
		}
	} else {
		netdev_err(adapter->netdev, "Get beacon state failed, err=%d\n",
			   err);
	}

	qlcnic_free_mbx_args(&cmd);

	return;
}
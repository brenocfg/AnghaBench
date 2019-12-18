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
typedef  scalar_t__ u32 ;
struct qlcnic_fw_dump {scalar_t__ enable; } ;
struct qlcnic_hardware_context {scalar_t__ reset_context; struct qlcnic_fw_dump fw_dump; } ;
struct qlcnic_adapter {int need_fw_reset; scalar_t__ heartbeat; scalar_t__ fw_fail_cnt; int flags; int /*<<< orphan*/  state; scalar_t__ dev_state; TYPE_1__* pdev; struct qlcnic_hardware_context* ahw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 scalar_t__ FW_FAIL_THRESH ; 
 int /*<<< orphan*/  QLCDB (struct qlcnic_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QLCNIC_CRB_DEV_STATE ; 
 scalar_t__ QLCNIC_CRB_PEG_NET_0 ; 
 scalar_t__ QLCNIC_CRB_PEG_NET_1 ; 
 scalar_t__ QLCNIC_CRB_PEG_NET_2 ; 
 scalar_t__ QLCNIC_CRB_PEG_NET_3 ; 
 scalar_t__ QLCNIC_CRB_PEG_NET_4 ; 
 scalar_t__ QLCNIC_DEV_NEED_QUISCENT ; 
 scalar_t__ QLCNIC_DEV_NEED_RESET ; 
 int QLCNIC_FWERROR_CODE (scalar_t__) ; 
 int QLCNIC_FW_HANG ; 
 int QLCNIC_FW_RESET_OWNER ; 
 int /*<<< orphan*/  QLCNIC_PEG_ALIVE_COUNTER ; 
 int /*<<< orphan*/  QLCNIC_PEG_HALT_STATUS1 ; 
 int /*<<< orphan*/  QLCNIC_PEG_HALT_STATUS2 ; 
 int /*<<< orphan*/  QLCRD32 (struct qlcnic_adapter*,scalar_t__,int*) ; 
 scalar_t__ QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __QLCNIC_FW_ATTACHED ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ qlcnic_auto_fw_reset ; 
 scalar_t__ qlcnic_check_temp (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_detach_work ; 
 int /*<<< orphan*/  qlcnic_dev_request_reset (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_dump_fw (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_reset_hw_context (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_schedule_work (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_set_npar_non_operational (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qlcnic_check_health(struct qlcnic_adapter *adapter)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	struct qlcnic_fw_dump *fw_dump = &ahw->fw_dump;
	u32 state = 0, heartbeat;
	u32 peg_status;
	int err = 0;

	if (qlcnic_check_temp(adapter))
		goto detach;

	if (adapter->need_fw_reset)
		qlcnic_dev_request_reset(adapter, 0);

	state = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DEV_STATE);
	if (state == QLCNIC_DEV_NEED_RESET) {
		qlcnic_set_npar_non_operational(adapter);
		adapter->need_fw_reset = 1;
	} else if (state == QLCNIC_DEV_NEED_QUISCENT)
		goto detach;

	heartbeat = QLC_SHARED_REG_RD32(adapter, QLCNIC_PEG_ALIVE_COUNTER);
	if (heartbeat != adapter->heartbeat) {
		adapter->heartbeat = heartbeat;
		adapter->fw_fail_cnt = 0;
		if (adapter->need_fw_reset)
			goto detach;

		if (ahw->reset_context && qlcnic_auto_fw_reset)
			qlcnic_reset_hw_context(adapter);

		return 0;
	}

	if (++adapter->fw_fail_cnt < FW_FAIL_THRESH)
		return 0;

	adapter->flags |= QLCNIC_FW_HANG;

	qlcnic_dev_request_reset(adapter, 0);

	if (qlcnic_auto_fw_reset)
		clear_bit(__QLCNIC_FW_ATTACHED, &adapter->state);

	dev_err(&adapter->pdev->dev, "firmware hang detected\n");
	peg_status = QLC_SHARED_REG_RD32(adapter, QLCNIC_PEG_HALT_STATUS1);
	dev_err(&adapter->pdev->dev, "Dumping hw/fw registers\n"
			"PEG_HALT_STATUS1: 0x%x, PEG_HALT_STATUS2: 0x%x,\n"
			"PEG_NET_0_PC: 0x%x, PEG_NET_1_PC: 0x%x,\n"
			"PEG_NET_2_PC: 0x%x, PEG_NET_3_PC: 0x%x,\n"
			"PEG_NET_4_PC: 0x%x\n",
			peg_status,
			QLC_SHARED_REG_RD32(adapter, QLCNIC_PEG_HALT_STATUS2),
			QLCRD32(adapter, QLCNIC_CRB_PEG_NET_0 + 0x3c, &err),
			QLCRD32(adapter, QLCNIC_CRB_PEG_NET_1 + 0x3c, &err),
			QLCRD32(adapter, QLCNIC_CRB_PEG_NET_2 + 0x3c, &err),
			QLCRD32(adapter, QLCNIC_CRB_PEG_NET_3 + 0x3c, &err),
			QLCRD32(adapter, QLCNIC_CRB_PEG_NET_4 + 0x3c, &err));
	if (QLCNIC_FWERROR_CODE(peg_status) == 0x67)
		dev_err(&adapter->pdev->dev,
			"Firmware aborted with error code 0x00006700. "
				"Device is being reset.\n");
detach:
	adapter->dev_state = (state == QLCNIC_DEV_NEED_QUISCENT) ? state :
		QLCNIC_DEV_NEED_RESET;

	if (qlcnic_auto_fw_reset && !test_and_set_bit(__QLCNIC_RESETTING,
						      &adapter->state)) {

		qlcnic_schedule_work(adapter, qlcnic_detach_work, 0);
		QLCDB(adapter, DRV, "fw recovery scheduled.\n");
	} else if (!qlcnic_auto_fw_reset && fw_dump->enable &&
		   adapter->flags & QLCNIC_FW_RESET_OWNER) {
		qlcnic_dump_fw(adapter);
	}

	return 1;
}
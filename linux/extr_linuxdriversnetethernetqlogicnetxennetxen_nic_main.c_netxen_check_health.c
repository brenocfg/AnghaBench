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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {int need_fw_reset; scalar_t__ heartbit; scalar_t__ fw_fail_cnt; int /*<<< orphan*/  state; TYPE_2__* pdev; TYPE_1__ ahw; struct net_device* netdev; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AUTO_FW_RESET_ENABLED ; 
 scalar_t__ FW_FAIL_THRESH ; 
 scalar_t__ NETXEN_CRB_PEG_NET_0 ; 
 scalar_t__ NETXEN_CRB_PEG_NET_1 ; 
 scalar_t__ NETXEN_CRB_PEG_NET_2 ; 
 scalar_t__ NETXEN_CRB_PEG_NET_3 ; 
 scalar_t__ NETXEN_CRB_PEG_NET_4 ; 
 scalar_t__ NETXEN_PEG_ALIVE_COUNTER ; 
 scalar_t__ NETXEN_PEG_HALT_STATUS1 ; 
 scalar_t__ NETXEN_PEG_HALT_STATUS2 ; 
 scalar_t__ NXRD32 (struct netxen_adapter*,scalar_t__) ; 
 scalar_t__ NX_CRB_DEV_STATE ; 
 scalar_t__ NX_DEV_FAILED ; 
 scalar_t__ NX_DEV_NEED_AER ; 
 scalar_t__ NX_DEV_NEED_RESET ; 
 int NX_FWERROR_PEGSTAT1 (scalar_t__) ; 
 scalar_t__ NX_IS_REVISION_P2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __NX_FW_ATTACHED ; 
 int /*<<< orphan*/  __NX_RESETTING ; 
 scalar_t__ auto_fw_reset ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  netxen_detach_work ; 
 scalar_t__ netxen_nic_check_temp (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_schedule_work (struct netxen_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nx_dev_request_reset (struct netxen_adapter*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
netxen_check_health(struct netxen_adapter *adapter)
{
	u32 state, heartbit;
	u32 peg_status;
	struct net_device *netdev = adapter->netdev;

	state = NXRD32(adapter, NX_CRB_DEV_STATE);
	if (state == NX_DEV_NEED_AER)
		return 0;

	if (netxen_nic_check_temp(adapter))
		goto detach;

	if (adapter->need_fw_reset) {
		if (nx_dev_request_reset(adapter))
			return 0;
		goto detach;
	}

	/* NX_DEV_NEED_RESET, this state can be marked in two cases
	 * 1. Tx timeout 2. Fw hang
	 * Send request to destroy context in case of tx timeout only
	 * and doesn't required in case of Fw hang
	 */
	if (state == NX_DEV_NEED_RESET || state == NX_DEV_FAILED) {
		adapter->need_fw_reset = 1;
		if (NX_IS_REVISION_P2(adapter->ahw.revision_id))
			goto detach;
	}

	if (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		return 0;

	heartbit = NXRD32(adapter, NETXEN_PEG_ALIVE_COUNTER);
	if (heartbit != adapter->heartbit) {
		adapter->heartbit = heartbit;
		adapter->fw_fail_cnt = 0;
		if (adapter->need_fw_reset)
			goto detach;
		return 0;
	}

	if (++adapter->fw_fail_cnt < FW_FAIL_THRESH)
		return 0;

	if (nx_dev_request_reset(adapter))
		return 0;

	clear_bit(__NX_FW_ATTACHED, &adapter->state);

	dev_err(&netdev->dev, "firmware hang detected\n");
	peg_status = NXRD32(adapter, NETXEN_PEG_HALT_STATUS1);
	dev_err(&adapter->pdev->dev, "Dumping hw/fw registers\n"
			"PEG_HALT_STATUS1: 0x%x, PEG_HALT_STATUS2: 0x%x,\n"
			"PEG_NET_0_PC: 0x%x, PEG_NET_1_PC: 0x%x,\n"
			"PEG_NET_2_PC: 0x%x, PEG_NET_3_PC: 0x%x,\n"
			"PEG_NET_4_PC: 0x%x\n",
			peg_status,
			NXRD32(adapter, NETXEN_PEG_HALT_STATUS2),
			NXRD32(adapter, NETXEN_CRB_PEG_NET_0 + 0x3c),
			NXRD32(adapter, NETXEN_CRB_PEG_NET_1 + 0x3c),
			NXRD32(adapter, NETXEN_CRB_PEG_NET_2 + 0x3c),
			NXRD32(adapter, NETXEN_CRB_PEG_NET_3 + 0x3c),
			NXRD32(adapter, NETXEN_CRB_PEG_NET_4 + 0x3c));
	if (NX_FWERROR_PEGSTAT1(peg_status) == 0x67)
		dev_err(&adapter->pdev->dev,
			"Firmware aborted with error code 0x00006700. "
				"Device is being reset.\n");
detach:
	if ((auto_fw_reset == AUTO_FW_RESET_ENABLED) &&
			!test_and_set_bit(__NX_RESETTING, &adapter->state))
		netxen_schedule_work(adapter, netxen_detach_work, 0);
	return 1;
}
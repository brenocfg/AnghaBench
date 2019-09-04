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
struct qlcnic_adapter {scalar_t__ tx_timeo_cnt; int need_fw_reset; TYPE_1__* ahw; int /*<<< orphan*/  state; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int reset_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_FORCE_FW_DUMP_KEY ; 
 scalar_t__ QLCNIC_MAX_TX_TIMEOUTS ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_tx_err (TYPE_1__*) ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_request_reset (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_dump_rings (struct qlcnic_adapter*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qlcnic_tx_timeout(struct net_device *netdev)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);

	if (test_bit(__QLCNIC_RESETTING, &adapter->state))
		return;

	qlcnic_dump_rings(adapter);

	if (++adapter->tx_timeo_cnt >= QLCNIC_MAX_TX_TIMEOUTS ||
	    netif_msg_tx_err(adapter->ahw)) {
		netdev_err(netdev, "Tx timeout, reset the adapter.\n");
		if (qlcnic_82xx_check(adapter))
			adapter->need_fw_reset = 1;
		else if (qlcnic_83xx_check(adapter))
			qlcnic_83xx_idc_request_reset(adapter,
						      QLCNIC_FORCE_FW_DUMP_KEY);
	} else {
		netdev_err(netdev, "Tx timeout, reset adapter context.\n");
		adapter->ahw->reset_context = 1;
	}
}
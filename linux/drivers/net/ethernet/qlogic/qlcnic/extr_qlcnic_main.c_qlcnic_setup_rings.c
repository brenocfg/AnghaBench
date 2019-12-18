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
struct qlcnic_adapter {scalar_t__ drv_tss_rings; scalar_t__ drv_rss_rings; scalar_t__ drv_tx_rings; scalar_t__ drv_sds_rings; int /*<<< orphan*/  state; TYPE_1__* pdev; int /*<<< orphan*/  msix_entries; struct net_device* netdev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  NETDEV_UP ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  __qlcnic_down (struct qlcnic_adapter*,struct net_device*) ; 
 int __qlcnic_up (struct qlcnic_adapter*,struct net_device*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_disable_mbx_poll (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_enable_mbx_poll (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_free_mbx_intr (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_initialize_nic (struct qlcnic_adapter*,int) ; 
 int qlcnic_83xx_setup_mbx_intr (struct qlcnic_adapter*) ; 
 int qlcnic_attach (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_detach (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_restore_indev_addr (struct net_device*,int /*<<< orphan*/ ) ; 
 int qlcnic_set_real_num_queues (struct qlcnic_adapter*,scalar_t__,scalar_t__) ; 
 int qlcnic_setup_intr (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_teardown_intr (struct qlcnic_adapter*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qlcnic_setup_rings(struct qlcnic_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	u8 tx_rings, rx_rings;
	int err;

	if (test_bit(__QLCNIC_RESETTING, &adapter->state))
		return -EBUSY;

	tx_rings = adapter->drv_tss_rings;
	rx_rings = adapter->drv_rss_rings;

	netif_device_detach(netdev);

	err = qlcnic_set_real_num_queues(adapter, tx_rings, rx_rings);
	if (err)
		goto done;

	if (netif_running(netdev))
		__qlcnic_down(adapter, netdev);

	qlcnic_detach(adapter);

	if (qlcnic_83xx_check(adapter)) {
		qlcnic_83xx_free_mbx_intr(adapter);
		qlcnic_83xx_enable_mbx_poll(adapter);
	}

	qlcnic_teardown_intr(adapter);

	err = qlcnic_setup_intr(adapter);
	if (err) {
		kfree(adapter->msix_entries);
		netdev_err(netdev, "failed to setup interrupt\n");
		return err;
	}

	/* Check if we need to update real_num_{tx|rx}_queues because
	 * qlcnic_setup_intr() may change Tx/Rx rings size
	 */
	if ((tx_rings != adapter->drv_tx_rings) ||
	    (rx_rings != adapter->drv_sds_rings)) {
		err = qlcnic_set_real_num_queues(adapter,
						 adapter->drv_tx_rings,
						 adapter->drv_sds_rings);
		if (err)
			goto done;
	}

	if (qlcnic_83xx_check(adapter)) {
		qlcnic_83xx_initialize_nic(adapter, 1);
		err = qlcnic_83xx_setup_mbx_intr(adapter);
		qlcnic_83xx_disable_mbx_poll(adapter);
		if (err) {
			dev_err(&adapter->pdev->dev,
				"failed to setup mbx interrupt\n");
			goto done;
		}
	}

	if (netif_running(netdev)) {
		err = qlcnic_attach(adapter);
		if (err)
			goto done;
		err = __qlcnic_up(adapter, netdev);
		if (err)
			goto done;
		qlcnic_restore_indev_addr(netdev, NETDEV_UP);
	}
done:
	netif_device_attach(netdev);
	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	return err;
}
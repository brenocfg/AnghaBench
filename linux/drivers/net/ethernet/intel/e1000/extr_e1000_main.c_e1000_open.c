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
struct net_device {int dummy; } ;
struct TYPE_2__ {int status; } ;
struct e1000_hw {TYPE_1__ mng_cookie; } ;
struct e1000_adapter {int /*<<< orphan*/  napi; int /*<<< orphan*/  flags; int /*<<< orphan*/  mng_vlan_id; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ICS_LSC ; 
 int E1000_MNG_DHCP_COOKIE_STATUS_VLAN_SUPPORT ; 
 int /*<<< orphan*/  E1000_MNG_VLAN_NONE ; 
 int E1000_SUCCESS ; 
 int EBUSY ; 
 int /*<<< orphan*/  ICS ; 
 int /*<<< orphan*/  __E1000_DOWN ; 
 int /*<<< orphan*/  __E1000_TESTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_configure (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_free_all_rx_resources (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_free_all_tx_resources (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_irq_enable (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_power_down_phy (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_power_up_phy (struct e1000_adapter*) ; 
 int e1000_request_irq (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_reset (struct e1000_adapter*) ; 
 int e1000_setup_all_rx_resources (struct e1000_adapter*) ; 
 int e1000_setup_all_tx_resources (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_update_mng_vlan (struct e1000_adapter*) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int e1000_open(struct net_device *netdev)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	int err;

	/* disallow open during test */
	if (test_bit(__E1000_TESTING, &adapter->flags))
		return -EBUSY;

	netif_carrier_off(netdev);

	/* allocate transmit descriptors */
	err = e1000_setup_all_tx_resources(adapter);
	if (err)
		goto err_setup_tx;

	/* allocate receive descriptors */
	err = e1000_setup_all_rx_resources(adapter);
	if (err)
		goto err_setup_rx;

	e1000_power_up_phy(adapter);

	adapter->mng_vlan_id = E1000_MNG_VLAN_NONE;
	if ((hw->mng_cookie.status &
			  E1000_MNG_DHCP_COOKIE_STATUS_VLAN_SUPPORT)) {
		e1000_update_mng_vlan(adapter);
	}

	/* before we allocate an interrupt, we must be ready to handle it.
	 * Setting DEBUG_SHIRQ in the kernel makes it fire an interrupt
	 * as soon as we call pci_request_irq, so we have to setup our
	 * clean_rx handler before we do so.
	 */
	e1000_configure(adapter);

	err = e1000_request_irq(adapter);
	if (err)
		goto err_req_irq;

	/* From here on the code is the same as e1000_up() */
	clear_bit(__E1000_DOWN, &adapter->flags);

	napi_enable(&adapter->napi);

	e1000_irq_enable(adapter);

	netif_start_queue(netdev);

	/* fire a link status change interrupt to start the watchdog */
	ew32(ICS, E1000_ICS_LSC);

	return E1000_SUCCESS;

err_req_irq:
	e1000_power_down_phy(adapter);
	e1000_free_all_rx_resources(adapter);
err_setup_rx:
	e1000_free_all_tx_resources(adapter);
err_setup_tx:
	e1000_reset(adapter);

	return err;
}
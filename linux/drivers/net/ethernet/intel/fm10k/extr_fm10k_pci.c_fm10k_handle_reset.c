#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  features; int /*<<< orphan*/  addr_assign_type; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  perm_addr; } ;
struct TYPE_5__ {int (* reset_hw ) (struct fm10k_hw*) ;int (* init_hw ) (struct fm10k_hw*) ;} ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ vlan_override; int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  addr; TYPE_1__ ops; } ;
struct fm10k_hw {TYPE_2__ mac; } ;
struct fm10k_intfc {int /*<<< orphan*/  state; TYPE_3__* pdev; struct fm10k_hw hw; struct net_device* netdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETIF_F_HW_VLAN_CTAG_RX ; 
 int /*<<< orphan*/  NET_ADDR_RANDOM ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __FM10K_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_clear_queueing_scheme (struct fm10k_intfc*) ; 
 int fm10k_hw_ready (struct fm10k_intfc*) ; 
 int fm10k_init_queueing_scheme (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_iov_resume (TYPE_3__*) ; 
 scalar_t__ fm10k_mac_vf ; 
 int /*<<< orphan*/  fm10k_mbx_free_irq (struct fm10k_intfc*) ; 
 int fm10k_mbx_request_irq (struct fm10k_intfc*) ; 
 int fm10k_open (struct net_device*) ; 
 int /*<<< orphan*/  fm10k_resume_macvlan_task (struct fm10k_intfc*) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pci_set_master (TYPE_3__*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int stub1 (struct fm10k_hw*) ; 
 int stub2 (struct fm10k_hw*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fm10k_handle_reset(struct fm10k_intfc *interface)
{
	struct net_device *netdev = interface->netdev;
	struct fm10k_hw *hw = &interface->hw;
	int err;

	WARN_ON(!test_bit(__FM10K_RESETTING, interface->state));

	rtnl_lock();

	pci_set_master(interface->pdev);

	/* reset and initialize the hardware so it is in a known state */
	err = hw->mac.ops.reset_hw(hw);
	if (err) {
		dev_err(&interface->pdev->dev, "reset_hw failed: %d\n", err);
		goto reinit_err;
	}

	err = hw->mac.ops.init_hw(hw);
	if (err) {
		dev_err(&interface->pdev->dev, "init_hw failed: %d\n", err);
		goto reinit_err;
	}

	err = fm10k_init_queueing_scheme(interface);
	if (err) {
		dev_err(&interface->pdev->dev,
			"init_queueing_scheme failed: %d\n", err);
		goto reinit_err;
	}

	/* re-associate interrupts */
	err = fm10k_mbx_request_irq(interface);
	if (err)
		goto err_mbx_irq;

	err = fm10k_hw_ready(interface);
	if (err)
		goto err_open;

	/* update hardware address for VFs if perm_addr has changed */
	if (hw->mac.type == fm10k_mac_vf) {
		if (is_valid_ether_addr(hw->mac.perm_addr)) {
			ether_addr_copy(hw->mac.addr, hw->mac.perm_addr);
			ether_addr_copy(netdev->perm_addr, hw->mac.perm_addr);
			ether_addr_copy(netdev->dev_addr, hw->mac.perm_addr);
			netdev->addr_assign_type &= ~NET_ADDR_RANDOM;
		}

		if (hw->mac.vlan_override)
			netdev->features &= ~NETIF_F_HW_VLAN_CTAG_RX;
		else
			netdev->features |= NETIF_F_HW_VLAN_CTAG_RX;
	}

	err = netif_running(netdev) ? fm10k_open(netdev) : 0;
	if (err)
		goto err_open;

	fm10k_iov_resume(interface->pdev);

	rtnl_unlock();

	fm10k_resume_macvlan_task(interface);

	clear_bit(__FM10K_RESETTING, interface->state);

	return err;
err_open:
	fm10k_mbx_free_irq(interface);
err_mbx_irq:
	fm10k_clear_queueing_scheme(interface);
reinit_err:
	netif_device_detach(netdev);

	rtnl_unlock();

	clear_bit(__FM10K_RESETTING, interface->state);

	return err;
}
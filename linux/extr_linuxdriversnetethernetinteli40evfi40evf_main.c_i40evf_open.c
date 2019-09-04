#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_2__ mac; } ;
struct i40evf_adapter {int flags; scalar_t__ state; int /*<<< orphan*/  crit_section; int /*<<< orphan*/  mac_vlan_list_lock; TYPE_3__ hw; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int I40EVF_FLAG_PF_COMMS_FAILED ; 
 scalar_t__ __I40EVF_DOWN ; 
 int /*<<< orphan*/  __I40EVF_IN_CRITICAL_TASK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i40evf_add_filter (struct i40evf_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40evf_configure (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  i40evf_down (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  i40evf_free_all_rx_resources (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  i40evf_free_all_tx_resources (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  i40evf_free_traffic_irqs (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  i40evf_irq_enable (struct i40evf_adapter*,int) ; 
 int i40evf_request_traffic_irqs (struct i40evf_adapter*,int /*<<< orphan*/ ) ; 
 int i40evf_setup_all_rx_resources (struct i40evf_adapter*) ; 
 int i40evf_setup_all_tx_resources (struct i40evf_adapter*) ; 
 int /*<<< orphan*/  i40evf_up_complete (struct i40evf_adapter*) ; 
 struct i40evf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int i40evf_open(struct net_device *netdev)
{
	struct i40evf_adapter *adapter = netdev_priv(netdev);
	int err;

	if (adapter->flags & I40EVF_FLAG_PF_COMMS_FAILED) {
		dev_err(&adapter->pdev->dev, "Unable to open device due to PF driver failure.\n");
		return -EIO;
	}

	while (test_and_set_bit(__I40EVF_IN_CRITICAL_TASK,
				&adapter->crit_section))
		usleep_range(500, 1000);

	if (adapter->state != __I40EVF_DOWN) {
		err = -EBUSY;
		goto err_unlock;
	}

	/* allocate transmit descriptors */
	err = i40evf_setup_all_tx_resources(adapter);
	if (err)
		goto err_setup_tx;

	/* allocate receive descriptors */
	err = i40evf_setup_all_rx_resources(adapter);
	if (err)
		goto err_setup_rx;

	/* clear any pending interrupts, may auto mask */
	err = i40evf_request_traffic_irqs(adapter, netdev->name);
	if (err)
		goto err_req_irq;

	spin_lock_bh(&adapter->mac_vlan_list_lock);

	i40evf_add_filter(adapter, adapter->hw.mac.addr);

	spin_unlock_bh(&adapter->mac_vlan_list_lock);

	i40evf_configure(adapter);

	i40evf_up_complete(adapter);

	i40evf_irq_enable(adapter, true);

	clear_bit(__I40EVF_IN_CRITICAL_TASK, &adapter->crit_section);

	return 0;

err_req_irq:
	i40evf_down(adapter);
	i40evf_free_traffic_irqs(adapter);
err_setup_rx:
	i40evf_free_all_rx_resources(adapter);
err_setup_tx:
	i40evf_free_all_tx_resources(adapter);
err_unlock:
	clear_bit(__I40EVF_IN_CRITICAL_TASK, &adapter->crit_section);

	return err;
}
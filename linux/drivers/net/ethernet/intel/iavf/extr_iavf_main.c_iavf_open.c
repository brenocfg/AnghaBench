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
struct iavf_adapter {int flags; scalar_t__ state; int /*<<< orphan*/  crit_section; int /*<<< orphan*/  mac_vlan_list_lock; TYPE_3__ hw; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int IAVF_FLAG_PF_COMMS_FAILED ; 
 scalar_t__ __IAVF_DOWN ; 
 int /*<<< orphan*/  __IAVF_IN_CRITICAL_TASK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iavf_add_filter (struct iavf_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iavf_configure (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_down (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_free_all_rx_resources (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_free_all_tx_resources (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_free_traffic_irqs (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_irq_enable (struct iavf_adapter*,int) ; 
 int iavf_request_traffic_irqs (struct iavf_adapter*,int /*<<< orphan*/ ) ; 
 int iavf_setup_all_rx_resources (struct iavf_adapter*) ; 
 int iavf_setup_all_tx_resources (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_up_complete (struct iavf_adapter*) ; 
 struct iavf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int iavf_open(struct net_device *netdev)
{
	struct iavf_adapter *adapter = netdev_priv(netdev);
	int err;

	if (adapter->flags & IAVF_FLAG_PF_COMMS_FAILED) {
		dev_err(&adapter->pdev->dev, "Unable to open device due to PF driver failure.\n");
		return -EIO;
	}

	while (test_and_set_bit(__IAVF_IN_CRITICAL_TASK,
				&adapter->crit_section))
		usleep_range(500, 1000);

	if (adapter->state != __IAVF_DOWN) {
		err = -EBUSY;
		goto err_unlock;
	}

	/* allocate transmit descriptors */
	err = iavf_setup_all_tx_resources(adapter);
	if (err)
		goto err_setup_tx;

	/* allocate receive descriptors */
	err = iavf_setup_all_rx_resources(adapter);
	if (err)
		goto err_setup_rx;

	/* clear any pending interrupts, may auto mask */
	err = iavf_request_traffic_irqs(adapter, netdev->name);
	if (err)
		goto err_req_irq;

	spin_lock_bh(&adapter->mac_vlan_list_lock);

	iavf_add_filter(adapter, adapter->hw.mac.addr);

	spin_unlock_bh(&adapter->mac_vlan_list_lock);

	iavf_configure(adapter);

	iavf_up_complete(adapter);

	iavf_irq_enable(adapter, true);

	clear_bit(__IAVF_IN_CRITICAL_TASK, &adapter->crit_section);

	return 0;

err_req_irq:
	iavf_down(adapter);
	iavf_free_traffic_irqs(adapter);
err_setup_rx:
	iavf_free_all_rx_resources(adapter);
err_setup_tx:
	iavf_free_all_tx_resources(adapter);
err_unlock:
	clear_bit(__IAVF_IN_CRITICAL_TASK, &adapter->crit_section);

	return err;
}
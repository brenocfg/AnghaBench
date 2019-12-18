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
struct virtchnl_vsi_resource {int dummy; } ;
struct virtchnl_vf_resource {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int watchdog_timeo; int features; int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  dev_addr; scalar_t__ max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct iavf_hw {TYPE_1__ mac; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; } ;
struct iavf_adapter {scalar_t__ state; int link_up; int netdev_registered; int rss_key_size; int rss_lut_size; TYPE_3__* vf_res; int /*<<< orphan*/  aq_required; void* rss_lut; void* rss_key; int /*<<< orphan*/  down_waitqueue; TYPE_2__ vsi; struct iavf_hw hw; int /*<<< orphan*/  flags; int /*<<< orphan*/  rx_desc_count; int /*<<< orphan*/  tx_desc_count; int /*<<< orphan*/  current_op; struct pci_dev* pdev; struct net_device* netdev; } ;
struct TYPE_6__ {int vf_cap_flags; } ;

/* Variables and functions */
 scalar_t__ CLIENT_ALLOWED (struct iavf_adapter*) ; 
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  IAVF_DEFAULT_RXD ; 
 int /*<<< orphan*/  IAVF_DEFAULT_TXD ; 
 int IAVF_ERR_ADMIN_QUEUE_NO_WORK ; 
 int IAVF_ERR_PARAM ; 
 int /*<<< orphan*/  IAVF_FLAG_AQ_CONFIGURE_RSS ; 
 int /*<<< orphan*/  IAVF_FLAG_RX_CSUM_ENABLED ; 
 int /*<<< orphan*/  IAVF_FLAG_WB_ON_ITR_CAPABLE ; 
 scalar_t__ IAVF_MAX_RXBUFFER ; 
 int IAVF_MAX_VF_VSI ; 
 scalar_t__ IAVF_PACKET_HDR_PAD ; 
 int NETIF_F_GRO ; 
 scalar_t__ RSS_AQ (struct iavf_adapter*) ; 
 int /*<<< orphan*/  VIRTCHNL_OP_UNKNOWN ; 
 int VIRTCHNL_VF_OFFLOAD_WB_ON_ITR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ __IAVF_DOWN ; 
 scalar_t__ __IAVF_INIT_GET_RESOURCES ; 
 int /*<<< orphan*/  __IAVF_VSI_DOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iavf_free_misc_irq (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_free_rss (struct iavf_adapter*) ; 
 int iavf_get_vf_config (struct iavf_adapter*) ; 
 int iavf_init_interrupt_scheme (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_init_rss (struct iavf_adapter*) ; 
 int iavf_lan_add_device (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_map_rings_to_vectors (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_misc_irq_enable (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_netdev_ops ; 
 scalar_t__ iavf_process_config (struct iavf_adapter*) ; 
 int iavf_request_misc_irq (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_reset_interrupt_capability (struct iavf_adapter*) ; 
 int iavf_send_vf_config_msg (struct iavf_adapter*) ; 
 int /*<<< orphan*/  iavf_set_ethtool_ops (struct net_device*) ; 
 int /*<<< orphan*/  iavf_shutdown_adminq (struct iavf_hw*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int register_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iavf_init_get_resources(struct iavf_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;
	struct iavf_hw *hw = &adapter->hw;
	int err = 0, bufsz;

	WARN_ON(adapter->state != __IAVF_INIT_GET_RESOURCES);
	/* aq msg sent, awaiting reply */
	if (!adapter->vf_res) {
		bufsz = sizeof(struct virtchnl_vf_resource) +
			(IAVF_MAX_VF_VSI *
			sizeof(struct virtchnl_vsi_resource));
		adapter->vf_res = kzalloc(bufsz, GFP_KERNEL);
		if (!adapter->vf_res)
			goto err;
	}
	err = iavf_get_vf_config(adapter);
	if (err == IAVF_ERR_ADMIN_QUEUE_NO_WORK) {
		err = iavf_send_vf_config_msg(adapter);
		goto err;
	} else if (err == IAVF_ERR_PARAM) {
		/* We only get ERR_PARAM if the device is in a very bad
		 * state or if we've been disabled for previous bad
		 * behavior. Either way, we're done now.
		 */
		iavf_shutdown_adminq(hw);
		dev_err(&pdev->dev, "Unable to get VF config due to PF error condition, not retrying\n");
		return 0;
	}
	if (err) {
		dev_err(&pdev->dev, "Unable to get VF config (%d)\n", err);
		goto err_alloc;
	}

	if (iavf_process_config(adapter))
		goto err_alloc;
	adapter->current_op = VIRTCHNL_OP_UNKNOWN;

	adapter->flags |= IAVF_FLAG_RX_CSUM_ENABLED;

	netdev->netdev_ops = &iavf_netdev_ops;
	iavf_set_ethtool_ops(netdev);
	netdev->watchdog_timeo = 5 * HZ;

	/* MTU range: 68 - 9710 */
	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = IAVF_MAX_RXBUFFER - IAVF_PACKET_HDR_PAD;

	if (!is_valid_ether_addr(adapter->hw.mac.addr)) {
		dev_info(&pdev->dev, "Invalid MAC address %pM, using random\n",
			 adapter->hw.mac.addr);
		eth_hw_addr_random(netdev);
		ether_addr_copy(adapter->hw.mac.addr, netdev->dev_addr);
	} else {
		ether_addr_copy(netdev->dev_addr, adapter->hw.mac.addr);
		ether_addr_copy(netdev->perm_addr, adapter->hw.mac.addr);
	}

	adapter->tx_desc_count = IAVF_DEFAULT_TXD;
	adapter->rx_desc_count = IAVF_DEFAULT_RXD;
	err = iavf_init_interrupt_scheme(adapter);
	if (err)
		goto err_sw_init;
	iavf_map_rings_to_vectors(adapter);
	if (adapter->vf_res->vf_cap_flags &
		VIRTCHNL_VF_OFFLOAD_WB_ON_ITR)
		adapter->flags |= IAVF_FLAG_WB_ON_ITR_CAPABLE;

	err = iavf_request_misc_irq(adapter);
	if (err)
		goto err_sw_init;

	netif_carrier_off(netdev);
	adapter->link_up = false;

	/* set the semaphore to prevent any callbacks after device registration
	 * up to time when state of driver will be set to __IAVF_DOWN
	 */
	rtnl_lock();
	if (!adapter->netdev_registered) {
		err = register_netdevice(netdev);
		if (err) {
			rtnl_unlock();
			goto err_register;
		}
	}

	adapter->netdev_registered = true;

	netif_tx_stop_all_queues(netdev);
	if (CLIENT_ALLOWED(adapter)) {
		err = iavf_lan_add_device(adapter);
		if (err) {
			rtnl_unlock();
			dev_info(&pdev->dev, "Failed to add VF to client API service list: %d\n",
				 err);
		}
	}
	dev_info(&pdev->dev, "MAC address: %pM\n", adapter->hw.mac.addr);
	if (netdev->features & NETIF_F_GRO)
		dev_info(&pdev->dev, "GRO is enabled\n");

	adapter->state = __IAVF_DOWN;
	set_bit(__IAVF_VSI_DOWN, adapter->vsi.state);
	rtnl_unlock();

	iavf_misc_irq_enable(adapter);
	wake_up(&adapter->down_waitqueue);

	adapter->rss_key = kzalloc(adapter->rss_key_size, GFP_KERNEL);
	adapter->rss_lut = kzalloc(adapter->rss_lut_size, GFP_KERNEL);
	if (!adapter->rss_key || !adapter->rss_lut)
		goto err_mem;
	if (RSS_AQ(adapter))
		adapter->aq_required |= IAVF_FLAG_AQ_CONFIGURE_RSS;
	else
		iavf_init_rss(adapter);

	return err;
err_mem:
	iavf_free_rss(adapter);
err_register:
	iavf_free_misc_irq(adapter);
err_sw_init:
	iavf_reset_interrupt_capability(adapter);
err_alloc:
	kfree(adapter->vf_res);
	adapter->vf_res = NULL;
err:
	return err;
}
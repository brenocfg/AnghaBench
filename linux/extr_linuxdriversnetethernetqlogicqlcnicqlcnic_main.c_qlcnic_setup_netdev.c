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
struct qlcnic_adapter {int rx_csum; int /*<<< orphan*/  dcb; int /*<<< orphan*/  drv_sds_rings; int /*<<< orphan*/  drv_tx_rings; TYPE_2__* msix_entries; TYPE_1__* ahw; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int watchdog_timeo; int features; int vlan_features; int hw_enc_features; int hw_features; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  irq; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  mtu; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  vector; } ;
struct TYPE_3__ {int capabilities; scalar_t__ mc_enabled; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IFF_UNICAST_FLT ; 
 int NETIF_F_GRO ; 
 int NETIF_F_GSO_UDP_TUNNEL ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_LRO ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int /*<<< orphan*/  P3P_MAX_MTU ; 
 int /*<<< orphan*/  P3P_MIN_MTU ; 
 int QLCNIC_FW_CAPABILITY_HW_LRO ; 
 scalar_t__ QLCNIC_IS_TSO_CAPABLE (struct qlcnic_adapter*) ; 
 int QLCNIC_WATCHDOG_TIMEOUTVALUE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  qlcnic_change_mtu (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_dcb_init_dcbnl_ops (int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_encap_rx_offload (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_encap_tx_offload (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_ethtool_ops ; 
 int /*<<< orphan*/  qlcnic_netdev_ops ; 
 int /*<<< orphan*/  qlcnic_set_mac_filter_count (struct qlcnic_adapter*) ; 
 int qlcnic_set_real_num_queues (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_sriov_vf_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_vf_ethtool_ops ; 
 scalar_t__ qlcnic_vlan_tx_check (struct qlcnic_adapter*) ; 
 int register_netdev (struct net_device*) ; 

int
qlcnic_setup_netdev(struct qlcnic_adapter *adapter, struct net_device *netdev,
		    int pci_using_dac)
{
	int err;
	struct pci_dev *pdev = adapter->pdev;

	adapter->rx_csum = 1;
	adapter->ahw->mc_enabled = 0;
	qlcnic_set_mac_filter_count(adapter);

	netdev->netdev_ops	   = &qlcnic_netdev_ops;
	netdev->watchdog_timeo     = QLCNIC_WATCHDOG_TIMEOUTVALUE * HZ;

	qlcnic_change_mtu(netdev, netdev->mtu);

	netdev->ethtool_ops = (qlcnic_sriov_vf_check(adapter)) ?
		&qlcnic_sriov_vf_ethtool_ops : &qlcnic_ethtool_ops;

	netdev->features |= (NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_RXCSUM |
			     NETIF_F_IPV6_CSUM | NETIF_F_GRO |
			     NETIF_F_HW_VLAN_CTAG_RX);
	netdev->vlan_features |= (NETIF_F_SG | NETIF_F_IP_CSUM |
				  NETIF_F_IPV6_CSUM);

	if (QLCNIC_IS_TSO_CAPABLE(adapter)) {
		netdev->features |= (NETIF_F_TSO | NETIF_F_TSO6);
		netdev->vlan_features |= (NETIF_F_TSO | NETIF_F_TSO6);
	}

	if (pci_using_dac) {
		netdev->features |= NETIF_F_HIGHDMA;
		netdev->vlan_features |= NETIF_F_HIGHDMA;
	}

	if (qlcnic_vlan_tx_check(adapter))
		netdev->features |= (NETIF_F_HW_VLAN_CTAG_TX);

	if (qlcnic_sriov_vf_check(adapter))
		netdev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;

	if (adapter->ahw->capabilities & QLCNIC_FW_CAPABILITY_HW_LRO)
		netdev->features |= NETIF_F_LRO;

	if (qlcnic_encap_tx_offload(adapter)) {
		netdev->features |= NETIF_F_GSO_UDP_TUNNEL;

		/* encapsulation Tx offload supported by Adapter */
		netdev->hw_enc_features = NETIF_F_IP_CSUM        |
					  NETIF_F_GSO_UDP_TUNNEL |
					  NETIF_F_TSO            |
					  NETIF_F_TSO6;
	}

	if (qlcnic_encap_rx_offload(adapter))
		netdev->hw_enc_features |= NETIF_F_RXCSUM;

	netdev->hw_features = netdev->features;
	netdev->priv_flags |= IFF_UNICAST_FLT;
	netdev->irq = adapter->msix_entries[0].vector;

	/* MTU range: 68 - 9600 */
	netdev->min_mtu = P3P_MIN_MTU;
	netdev->max_mtu = P3P_MAX_MTU;

	err = qlcnic_set_real_num_queues(adapter, adapter->drv_tx_rings,
					 adapter->drv_sds_rings);
	if (err)
		return err;

	qlcnic_dcb_init_dcbnl_ops(adapter->dcb);

	err = register_netdev(netdev);
	if (err) {
		dev_err(&pdev->dev, "failed to register net device\n");
		return err;
	}

	return 0;
}
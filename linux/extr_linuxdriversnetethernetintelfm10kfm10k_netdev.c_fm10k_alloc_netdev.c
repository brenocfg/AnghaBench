#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {int features; int hw_enc_features; int vlan_features; int hw_features; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/ * netdev_ops; } ;
struct fm10k_intfc {scalar_t__ msg_enable; } ;
struct fm10k_info {scalar_t__ mac; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFAULT_DEBUG_LEVEL_SHIFT ; 
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 int /*<<< orphan*/  FM10K_MAX_JUMBO_FRAME_SIZE ; 
 int /*<<< orphan*/  IFF_UNICAST_FLT ; 
 int /*<<< orphan*/  MAX_QUEUES ; 
 int NETIF_F_GSO_UDP_TUNNEL ; 
 int NETIF_F_HW_L2FW_DOFFLOAD ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_RXHASH ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int NETIF_F_TSO_ECN ; 
 struct net_device* alloc_etherdev_mq (int,int /*<<< orphan*/ ) ; 
 scalar_t__ fm10k_mac_pf ; 
 int /*<<< orphan*/  fm10k_netdev_ops ; 
 int /*<<< orphan*/  fm10k_set_ethtool_ops (struct net_device*) ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 

struct net_device *fm10k_alloc_netdev(const struct fm10k_info *info)
{
	netdev_features_t hw_features;
	struct fm10k_intfc *interface;
	struct net_device *dev;

	dev = alloc_etherdev_mq(sizeof(struct fm10k_intfc), MAX_QUEUES);
	if (!dev)
		return NULL;

	/* set net device and ethtool ops */
	dev->netdev_ops = &fm10k_netdev_ops;
	fm10k_set_ethtool_ops(dev);

	/* configure default debug level */
	interface = netdev_priv(dev);
	interface->msg_enable = BIT(DEFAULT_DEBUG_LEVEL_SHIFT) - 1;

	/* configure default features */
	dev->features |= NETIF_F_IP_CSUM |
			 NETIF_F_IPV6_CSUM |
			 NETIF_F_SG |
			 NETIF_F_TSO |
			 NETIF_F_TSO6 |
			 NETIF_F_TSO_ECN |
			 NETIF_F_RXHASH |
			 NETIF_F_RXCSUM;

	/* Only the PF can support VXLAN and NVGRE tunnel offloads */
	if (info->mac == fm10k_mac_pf) {
		dev->hw_enc_features = NETIF_F_IP_CSUM |
				       NETIF_F_TSO |
				       NETIF_F_TSO6 |
				       NETIF_F_TSO_ECN |
				       NETIF_F_GSO_UDP_TUNNEL |
				       NETIF_F_IPV6_CSUM |
				       NETIF_F_SG;

		dev->features |= NETIF_F_GSO_UDP_TUNNEL;
	}

	/* all features defined to this point should be changeable */
	hw_features = dev->features;

	/* allow user to enable L2 forwarding acceleration */
	hw_features |= NETIF_F_HW_L2FW_DOFFLOAD;

	/* configure VLAN features */
	dev->vlan_features |= dev->features;

	/* we want to leave these both on as we cannot disable VLAN tag
	 * insertion or stripping on the hardware since it is contained
	 * in the FTAG and not in the frame itself.
	 */
	dev->features |= NETIF_F_HW_VLAN_CTAG_TX |
			 NETIF_F_HW_VLAN_CTAG_RX |
			 NETIF_F_HW_VLAN_CTAG_FILTER;

	dev->priv_flags |= IFF_UNICAST_FLT;

	dev->hw_features |= hw_features;

	/* MTU range: 68 - 15342 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = FM10K_MAX_JUMBO_FRAME_SIZE;

	return dev;
}
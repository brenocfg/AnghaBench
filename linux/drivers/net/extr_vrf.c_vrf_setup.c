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
struct net_device {int needs_free_netdev; int features; int hw_features; int hw_enc_features; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * l3mdev_ops; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_MAX_MTU ; 
 int /*<<< orphan*/  IFF_LIVE_ADDR_CHANGE ; 
 int /*<<< orphan*/  IFF_NO_QUEUE ; 
 int /*<<< orphan*/  IFF_NO_RX_HANDLER ; 
 int /*<<< orphan*/  IPV6_MIN_MTU ; 
 int NETIF_F_FRAGLIST ; 
 int NETIF_F_GSO_SOFTWARE ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_LLTX ; 
 int NETIF_F_NETNS_LOCAL ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SCTP_CRC ; 
 int NETIF_F_SG ; 
 int NETIF_F_VLAN_CHALLENGED ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  vrf_ethtool_ops ; 
 int /*<<< orphan*/  vrf_l3mdev_ops ; 
 int /*<<< orphan*/  vrf_netdev_ops ; 

__attribute__((used)) static void vrf_setup(struct net_device *dev)
{
	ether_setup(dev);

	/* Initialize the device structure. */
	dev->netdev_ops = &vrf_netdev_ops;
	dev->l3mdev_ops = &vrf_l3mdev_ops;
	dev->ethtool_ops = &vrf_ethtool_ops;
	dev->needs_free_netdev = true;

	/* Fill in device structure with ethernet-generic values. */
	eth_hw_addr_random(dev);

	/* don't acquire vrf device's netif_tx_lock when transmitting */
	dev->features |= NETIF_F_LLTX;

	/* don't allow vrf devices to change network namespaces. */
	dev->features |= NETIF_F_NETNS_LOCAL;

	/* does not make sense for a VLAN to be added to a vrf device */
	dev->features   |= NETIF_F_VLAN_CHALLENGED;

	/* enable offload features */
	dev->features   |= NETIF_F_GSO_SOFTWARE;
	dev->features   |= NETIF_F_RXCSUM | NETIF_F_HW_CSUM | NETIF_F_SCTP_CRC;
	dev->features   |= NETIF_F_SG | NETIF_F_FRAGLIST | NETIF_F_HIGHDMA;

	dev->hw_features = dev->features;
	dev->hw_enc_features = dev->features;

	/* default to no qdisc; user can add if desired */
	dev->priv_flags |= IFF_NO_QUEUE;
	dev->priv_flags |= IFF_NO_RX_HANDLER;
	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE;

	/* VRF devices do not care about MTU, but if the MTU is set
	 * too low then the ipv4 and ipv6 protocols are disabled
	 * which breaks networking.
	 */
	dev->min_mtu = IPV6_MIN_MTU;
	dev->max_mtu = ETH_MAX_MTU;
}
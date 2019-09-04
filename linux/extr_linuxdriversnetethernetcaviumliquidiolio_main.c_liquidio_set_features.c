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
struct net_device {int features; } ;
struct lio {int dev_capability; int enc_dev_capability; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_LRO ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  OCTNET_CMD_LRO_DISABLE ; 
 int /*<<< orphan*/  OCTNET_CMD_LRO_ENABLE ; 
 int /*<<< orphan*/  OCTNET_CMD_RXCSUM_DISABLE ; 
 int /*<<< orphan*/  OCTNET_CMD_RXCSUM_ENABLE ; 
 int /*<<< orphan*/  OCTNET_CMD_TNL_RX_CSUM_CTL ; 
 int /*<<< orphan*/  OCTNET_CMD_VLAN_FILTER_CTL ; 
 int OCTNET_CMD_VLAN_FILTER_DISABLE ; 
 int OCTNET_CMD_VLAN_FILTER_ENABLE ; 
 int OCTNIC_LROIPV4 ; 
 int OCTNIC_LROIPV6 ; 
 int /*<<< orphan*/  liquidio_set_feature (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  liquidio_set_rxcsum_command (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lio* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int liquidio_set_features(struct net_device *netdev,
				 netdev_features_t features)
{
	struct lio *lio = netdev_priv(netdev);

	if ((features & NETIF_F_LRO) &&
	    (lio->dev_capability & NETIF_F_LRO) &&
	    !(netdev->features & NETIF_F_LRO))
		liquidio_set_feature(netdev, OCTNET_CMD_LRO_ENABLE,
				     OCTNIC_LROIPV4 | OCTNIC_LROIPV6);
	else if (!(features & NETIF_F_LRO) &&
		 (lio->dev_capability & NETIF_F_LRO) &&
		 (netdev->features & NETIF_F_LRO))
		liquidio_set_feature(netdev, OCTNET_CMD_LRO_DISABLE,
				     OCTNIC_LROIPV4 | OCTNIC_LROIPV6);

	/* Sending command to firmware to enable/disable RX checksum
	 * offload settings using ethtool
	 */
	if (!(netdev->features & NETIF_F_RXCSUM) &&
	    (lio->enc_dev_capability & NETIF_F_RXCSUM) &&
	    (features & NETIF_F_RXCSUM))
		liquidio_set_rxcsum_command(netdev,
					    OCTNET_CMD_TNL_RX_CSUM_CTL,
					    OCTNET_CMD_RXCSUM_ENABLE);
	else if ((netdev->features & NETIF_F_RXCSUM) &&
		 (lio->enc_dev_capability & NETIF_F_RXCSUM) &&
		 !(features & NETIF_F_RXCSUM))
		liquidio_set_rxcsum_command(netdev, OCTNET_CMD_TNL_RX_CSUM_CTL,
					    OCTNET_CMD_RXCSUM_DISABLE);

	if ((features & NETIF_F_HW_VLAN_CTAG_FILTER) &&
	    (lio->dev_capability & NETIF_F_HW_VLAN_CTAG_FILTER) &&
	    !(netdev->features & NETIF_F_HW_VLAN_CTAG_FILTER))
		liquidio_set_feature(netdev, OCTNET_CMD_VLAN_FILTER_CTL,
				     OCTNET_CMD_VLAN_FILTER_ENABLE);
	else if (!(features & NETIF_F_HW_VLAN_CTAG_FILTER) &&
		 (lio->dev_capability & NETIF_F_HW_VLAN_CTAG_FILTER) &&
		 (netdev->features & NETIF_F_HW_VLAN_CTAG_FILTER))
		liquidio_set_feature(netdev, OCTNET_CMD_VLAN_FILTER_CTL,
				     OCTNET_CMD_VLAN_FILTER_DISABLE);

	return 0;
}
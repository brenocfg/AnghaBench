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
struct sky2_port {struct sky2_hw* hw; } ;
struct sky2_hw {scalar_t__ chip_id; int flags; } ;
struct net_device {scalar_t__ mtu; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 scalar_t__ CHIP_ID_YUKON_EC_U ; 
 scalar_t__ ETH_DATA_LEN ; 
 int NETIF_F_CSUM_MASK ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_RXHASH ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int SKY2_HW_RSS_CHKSUM ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static netdev_features_t sky2_fix_features(struct net_device *dev,
	netdev_features_t features)
{
	const struct sky2_port *sky2 = netdev_priv(dev);
	const struct sky2_hw *hw = sky2->hw;

	/* In order to do Jumbo packets on these chips, need to turn off the
	 * transmit store/forward. Therefore checksum offload won't work.
	 */
	if (dev->mtu > ETH_DATA_LEN && hw->chip_id == CHIP_ID_YUKON_EC_U) {
		netdev_info(dev, "checksum offload not possible with jumbo frames\n");
		features &= ~(NETIF_F_TSO | NETIF_F_SG | NETIF_F_CSUM_MASK);
	}

	/* Some hardware requires receive checksum for RSS to work. */
	if ( (features & NETIF_F_RXHASH) &&
	     !(features & NETIF_F_RXCSUM) &&
	     (sky2->hw->flags & SKY2_HW_RSS_CHKSUM)) {
		netdev_info(dev, "receive hashing forces receive checksum\n");
		features |= NETIF_F_RXCSUM;
	}

	return features;
}
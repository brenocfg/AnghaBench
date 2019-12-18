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
struct net_device {int mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG0_MAXLEN_MASK ; 
 int CONFIG0_MAXLEN_SHIFT ; 
 int EINVAL ; 
 int /*<<< orphan*/  gmac_disable_tx_rx (struct net_device*) ; 
 int /*<<< orphan*/  gmac_enable_tx_rx (struct net_device*) ; 
 int gmac_pick_rx_max_len (int) ; 
 int /*<<< orphan*/  gmac_update_config0_reg (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_update_features (struct net_device*) ; 

__attribute__((used)) static int gmac_change_mtu(struct net_device *netdev, int new_mtu)
{
	int max_len = gmac_pick_rx_max_len(new_mtu);

	if (max_len < 0)
		return -EINVAL;

	gmac_disable_tx_rx(netdev);

	netdev->mtu = new_mtu;
	gmac_update_config0_reg(netdev, max_len << CONFIG0_MAXLEN_SHIFT,
				CONFIG0_MAXLEN_MASK);

	netdev_update_features(netdev);

	gmac_enable_tx_rx(netdev);

	return 0;
}
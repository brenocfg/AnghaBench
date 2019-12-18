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
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  alloc; } ;
struct TYPE_3__ {int /*<<< orphan*/  alloc; } ;
struct ksz_hw {TYPE_2__ rx_desc_info; TYPE_1__ tx_desc_info; } ;
struct ethtool_ringparam {int tx_max_pending; int rx_max_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_pending; } ;
struct dev_priv {struct dev_info* adapter; } ;
struct dev_info {struct ksz_hw hw; } ;

/* Variables and functions */
 struct dev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void netdev_get_ringparam(struct net_device *dev,
	struct ethtool_ringparam *ring)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;

	ring->tx_max_pending = (1 << 9);
	ring->tx_pending = hw->tx_desc_info.alloc;
	ring->rx_max_pending = (1 << 9);
	ring->rx_pending = hw->rx_desc_info.alloc;
}
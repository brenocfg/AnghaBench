#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; } ;
struct aq_nic_s {int dummy; } ;
struct aq_nic_cfg_s {TYPE_1__* aq_hw_caps; int /*<<< orphan*/  txds; int /*<<< orphan*/  rxds; } ;
struct TYPE_2__ {int /*<<< orphan*/  txds_max; int /*<<< orphan*/  rxds_max; } ;

/* Variables and functions */
 struct aq_nic_cfg_s* aq_nic_get_cfg (struct aq_nic_s*) ; 
 struct aq_nic_s* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void aq_get_ringparam(struct net_device *ndev,
			     struct ethtool_ringparam *ring)
{
	struct aq_nic_s *aq_nic = netdev_priv(ndev);
	struct aq_nic_cfg_s *aq_nic_cfg = aq_nic_get_cfg(aq_nic);

	ring->rx_pending = aq_nic_cfg->rxds;
	ring->tx_pending = aq_nic_cfg->txds;

	ring->rx_max_pending = aq_nic_cfg->aq_hw_caps->rxds_max;
	ring->tx_max_pending = aq_nic_cfg->aq_hw_caps->txds_max;
}
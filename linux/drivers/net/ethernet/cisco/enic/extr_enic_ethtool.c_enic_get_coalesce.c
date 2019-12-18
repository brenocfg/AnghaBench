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
struct net_device {int dummy; } ;
struct ethtool_coalesce {int use_adaptive_rx_coalesce; int /*<<< orphan*/  rx_coalesce_usecs_high; int /*<<< orphan*/  rx_coalesce_usecs_low; int /*<<< orphan*/  rx_coalesce_usecs; int /*<<< orphan*/  tx_coalesce_usecs; } ;
struct enic_rx_coal {int /*<<< orphan*/  range_end; int /*<<< orphan*/  small_pkt_range_start; scalar_t__ use_adaptive_rx_coalesce; } ;
struct enic {int /*<<< orphan*/  rx_coalesce_usecs; int /*<<< orphan*/  tx_coalesce_usecs; int /*<<< orphan*/  vdev; struct enic_rx_coal rx_coalesce_setting; } ;

/* Variables and functions */
 scalar_t__ VNIC_DEV_INTR_MODE_MSIX ; 
 struct enic* netdev_priv (struct net_device*) ; 
 scalar_t__ vnic_dev_get_intr_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enic_get_coalesce(struct net_device *netdev,
	struct ethtool_coalesce *ecmd)
{
	struct enic *enic = netdev_priv(netdev);
	struct enic_rx_coal *rxcoal = &enic->rx_coalesce_setting;

	if (vnic_dev_get_intr_mode(enic->vdev) == VNIC_DEV_INTR_MODE_MSIX)
		ecmd->tx_coalesce_usecs = enic->tx_coalesce_usecs;
	ecmd->rx_coalesce_usecs = enic->rx_coalesce_usecs;
	if (rxcoal->use_adaptive_rx_coalesce)
		ecmd->use_adaptive_rx_coalesce = 1;
	ecmd->rx_coalesce_usecs_low = rxcoal->small_pkt_range_start;
	ecmd->rx_coalesce_usecs_high = rxcoal->range_end;

	return 0;
}
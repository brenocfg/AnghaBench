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
struct param_range {void* count; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_2__ {struct param_range cbs; struct param_range rfds; } ;
struct nic {int /*<<< orphan*/  netdev; TYPE_1__ params; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e100_down (struct nic*) ; 
 int /*<<< orphan*/  e100_up (struct nic*) ; 
 void* max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* min (void*,int /*<<< orphan*/ ) ; 
 struct nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*,void*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int e100_set_ringparam(struct net_device *netdev,
	struct ethtool_ringparam *ring)
{
	struct nic *nic = netdev_priv(netdev);
	struct param_range *rfds = &nic->params.rfds;
	struct param_range *cbs = &nic->params.cbs;

	if ((ring->rx_mini_pending) || (ring->rx_jumbo_pending))
		return -EINVAL;

	if (netif_running(netdev))
		e100_down(nic);
	rfds->count = max(ring->rx_pending, rfds->min);
	rfds->count = min(rfds->count, rfds->max);
	cbs->count = max(ring->tx_pending, cbs->min);
	cbs->count = min(cbs->count, cbs->max);
	netif_info(nic, drv, nic->netdev, "Ring Param settings: rx: %d, tx %d\n",
		   rfds->count, cbs->count);
	if (netif_running(netdev))
		e100_up(nic);

	return 0;
}
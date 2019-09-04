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
struct vnic_enet_config {int /*<<< orphan*/  wq_desc_count; int /*<<< orphan*/  rq_desc_count; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  rx_max_pending; } ;
struct enic {struct vnic_enet_config config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENIC_MAX_RQ_DESCS ; 
 int /*<<< orphan*/  ENIC_MAX_WQ_DESCS ; 
 struct enic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void enic_get_ringparam(struct net_device *netdev,
			       struct ethtool_ringparam *ring)
{
	struct enic *enic = netdev_priv(netdev);
	struct vnic_enet_config *c = &enic->config;

	ring->rx_max_pending = ENIC_MAX_RQ_DESCS;
	ring->rx_pending = c->rq_desc_count;
	ring->tx_max_pending = ENIC_MAX_WQ_DESCS;
	ring->tx_pending = c->wq_desc_count;
}
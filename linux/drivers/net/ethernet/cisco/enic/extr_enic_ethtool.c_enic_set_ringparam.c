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
struct vnic_enet_config {unsigned int rq_desc_count; unsigned int wq_desc_count; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int rx_pending; int tx_pending; scalar_t__ rx_jumbo_pending; scalar_t__ rx_jumbo_max_pending; scalar_t__ rx_mini_pending; scalar_t__ rx_mini_max_pending; } ;
struct enic {struct vnic_enet_config config; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENIC_MAX_RQ_DESCS ; 
 int ENIC_MAX_WQ_DESCS ; 
 int ENIC_MIN_RQ_DESCS ; 
 int ENIC_MIN_WQ_DESCS ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int dev_open (struct net_device*,int /*<<< orphan*/ *) ; 
 int enic_alloc_vnic_resources (struct enic*) ; 
 int /*<<< orphan*/  enic_free_vnic_resources (struct enic*) ; 
 int /*<<< orphan*/  enic_init_vnic_resources (struct enic*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 struct enic* netdev_priv (struct net_device*) ; 
 int netif_running (struct net_device*) ; 

__attribute__((used)) static int enic_set_ringparam(struct net_device *netdev,
			      struct ethtool_ringparam *ring)
{
	struct enic *enic = netdev_priv(netdev);
	struct vnic_enet_config *c = &enic->config;
	int running = netif_running(netdev);
	unsigned int rx_pending;
	unsigned int tx_pending;
	int err = 0;

	if (ring->rx_mini_max_pending || ring->rx_mini_pending) {
		netdev_info(netdev,
			    "modifying mini ring params is not supported");
		return -EINVAL;
	}
	if (ring->rx_jumbo_max_pending || ring->rx_jumbo_pending) {
		netdev_info(netdev,
			    "modifying jumbo ring params is not supported");
		return -EINVAL;
	}
	rx_pending = c->rq_desc_count;
	tx_pending = c->wq_desc_count;
	if (ring->rx_pending > ENIC_MAX_RQ_DESCS ||
	    ring->rx_pending < ENIC_MIN_RQ_DESCS) {
		netdev_info(netdev, "rx pending (%u) not in range [%u,%u]",
			    ring->rx_pending, ENIC_MIN_RQ_DESCS,
			    ENIC_MAX_RQ_DESCS);
		return -EINVAL;
	}
	if (ring->tx_pending > ENIC_MAX_WQ_DESCS ||
	    ring->tx_pending < ENIC_MIN_WQ_DESCS) {
		netdev_info(netdev, "tx pending (%u) not in range [%u,%u]",
			    ring->tx_pending, ENIC_MIN_WQ_DESCS,
			    ENIC_MAX_WQ_DESCS);
		return -EINVAL;
	}
	if (running)
		dev_close(netdev);
	c->rq_desc_count =
		ring->rx_pending & 0xffffffe0; /* must be aligned to groups of 32 */
	c->wq_desc_count =
		ring->tx_pending & 0xffffffe0; /* must be aligned to groups of 32 */
	enic_free_vnic_resources(enic);
	err = enic_alloc_vnic_resources(enic);
	if (err) {
		netdev_err(netdev,
			   "Failed to alloc vNIC resources, aborting\n");
		enic_free_vnic_resources(enic);
		goto err_out;
	}
	enic_init_vnic_resources(enic);
	if (running) {
		err = dev_open(netdev, NULL);
		if (err)
			goto err_out;
	}
	return 0;
err_out:
	c->rq_desc_count = rx_pending;
	c->wq_desc_count = tx_pending;
	return err;
}
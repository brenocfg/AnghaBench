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
struct net_device {int /*<<< orphan*/  rx_cpu_rmap; } ;
struct bnxt {int flags; int /*<<< orphan*/  rx_nr_rings; scalar_t__ tx_nr_rings_xdp; scalar_t__ tx_nr_rings; struct net_device* dev; } ;

/* Variables and functions */
 int BNXT_FLAG_RFS ; 
 int /*<<< orphan*/  alloc_irq_cpu_rmap (int /*<<< orphan*/ ) ; 
 int netif_set_real_num_rx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int netif_set_real_num_tx_queues (struct net_device*,scalar_t__) ; 

__attribute__((used)) static int bnxt_set_real_num_queues(struct bnxt *bp)
{
	int rc;
	struct net_device *dev = bp->dev;

	rc = netif_set_real_num_tx_queues(dev, bp->tx_nr_rings -
					  bp->tx_nr_rings_xdp);
	if (rc)
		return rc;

	rc = netif_set_real_num_rx_queues(dev, bp->rx_nr_rings);
	if (rc)
		return rc;

#ifdef CONFIG_RFS_ACCEL
	if (bp->flags & BNXT_FLAG_RFS)
		dev->rx_cpu_rmap = alloc_irq_cpu_rmap(bp->rx_nr_rings);
#endif

	return rc;
}
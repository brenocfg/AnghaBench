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
typedef  int u32 ;
struct net_device {unsigned int num_tx_queues; } ;
struct ethtool_coalesce {scalar_t__ tx_max_coalesced_frames; int tx_coalesce_usecs; scalar_t__ rx_max_coalesced_frames; int rx_coalesce_usecs; scalar_t__ use_adaptive_rx_coalesce; scalar_t__ use_adaptive_tx_coalesce; } ;
struct dim_cq_moder {int usec; int pkts; } ;
struct TYPE_3__ {int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {scalar_t__ use_dim; TYPE_1__ dim; } ;
struct bcm_sysport_priv {int rx_coalesce_usecs; int rx_max_coalesced_frames; TYPE_2__ dim; int /*<<< orphan*/ * tx_rings; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RDMA_INTR_THRESH_MASK ; 
 int RDMA_TIMEOUT_MASK ; 
 scalar_t__ RING_INTR_THRESH_MASK ; 
 int RING_TIMEOUT_MASK ; 
 int /*<<< orphan*/  bcm_sysport_set_rx_coalesce (struct bcm_sysport_priv*,int,int) ; 
 int /*<<< orphan*/  bcm_sysport_set_tx_coalesce (int /*<<< orphan*/ *,struct ethtool_coalesce*) ; 
 struct dim_cq_moder net_dim_get_def_rx_moderation (int /*<<< orphan*/ ) ; 
 struct bcm_sysport_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bcm_sysport_set_coalesce(struct net_device *dev,
				    struct ethtool_coalesce *ec)
{
	struct bcm_sysport_priv *priv = netdev_priv(dev);
	struct dim_cq_moder moder;
	u32 usecs, pkts;
	unsigned int i;

	/* Base system clock is 125Mhz, DMA timeout is this reference clock
	 * divided by 1024, which yield roughly 8.192 us, our maximum value has
	 * to fit in the RING_TIMEOUT_MASK (16 bits).
	 */
	if (ec->tx_max_coalesced_frames > RING_INTR_THRESH_MASK ||
	    ec->tx_coalesce_usecs > (RING_TIMEOUT_MASK * 8) + 1 ||
	    ec->rx_max_coalesced_frames > RDMA_INTR_THRESH_MASK ||
	    ec->rx_coalesce_usecs > (RDMA_TIMEOUT_MASK * 8) + 1)
		return -EINVAL;

	if ((ec->tx_coalesce_usecs == 0 && ec->tx_max_coalesced_frames == 0) ||
	    (ec->rx_coalesce_usecs == 0 && ec->rx_max_coalesced_frames == 0) ||
	    ec->use_adaptive_tx_coalesce)
		return -EINVAL;

	for (i = 0; i < dev->num_tx_queues; i++)
		bcm_sysport_set_tx_coalesce(&priv->tx_rings[i], ec);

	priv->rx_coalesce_usecs = ec->rx_coalesce_usecs;
	priv->rx_max_coalesced_frames = ec->rx_max_coalesced_frames;
	usecs = priv->rx_coalesce_usecs;
	pkts = priv->rx_max_coalesced_frames;

	if (ec->use_adaptive_rx_coalesce && !priv->dim.use_dim) {
		moder = net_dim_get_def_rx_moderation(priv->dim.dim.mode);
		usecs = moder.usec;
		pkts = moder.pkts;
	}

	priv->dim.use_dim = ec->use_adaptive_rx_coalesce;

	/* Apply desired coalescing parameters */
	bcm_sysport_set_rx_coalesce(priv, usecs, pkts);

	return 0;
}
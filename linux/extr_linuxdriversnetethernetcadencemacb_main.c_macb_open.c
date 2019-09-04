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
struct net_device {size_t mtu; int /*<<< orphan*/  phydev; } ;
struct macb_queue {int /*<<< orphan*/  napi; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* mog_init_rings ) (struct macb*) ;} ;
struct macb {unsigned int num_queues; TYPE_2__* ptp_info; struct macb_queue* queues; TYPE_1__ macbgem_ops; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* ptp_init ) (struct net_device*) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 size_t ETH_FCS_LEN ; 
 size_t ETH_HLEN ; 
 size_t NET_IP_ALIGN ; 
 int macb_alloc_consistent (struct macb*) ; 
 int /*<<< orphan*/  macb_init_hw (struct macb*) ; 
 int /*<<< orphan*/  macb_init_rx_buffer_size (struct macb*,size_t) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct macb* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct macb*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*) ; 

__attribute__((used)) static int macb_open(struct net_device *dev)
{
	struct macb *bp = netdev_priv(dev);
	size_t bufsz = dev->mtu + ETH_HLEN + ETH_FCS_LEN + NET_IP_ALIGN;
	struct macb_queue *queue;
	unsigned int q;
	int err;

	netdev_dbg(bp->dev, "open\n");

	/* carrier starts down */
	netif_carrier_off(dev);

	/* if the phy is not yet register, retry later*/
	if (!dev->phydev)
		return -EAGAIN;

	/* RX buffers initialization */
	macb_init_rx_buffer_size(bp, bufsz);

	err = macb_alloc_consistent(bp);
	if (err) {
		netdev_err(dev, "Unable to allocate DMA memory (error %d)\n",
			   err);
		return err;
	}

	bp->macbgem_ops.mog_init_rings(bp);
	macb_init_hw(bp);

	for (q = 0, queue = bp->queues; q < bp->num_queues; ++q, ++queue)
		napi_enable(&queue->napi);

	/* schedule a link state check */
	phy_start(dev->phydev);

	netif_tx_start_all_queues(dev);

	if (bp->ptp_info)
		bp->ptp_info->ptp_init(dev);

	return 0;
}
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
struct tx_desc {int dummy; } ;
struct rx_desc {int dummy; } ;
struct rhine_private {int quirks; void* tx_bufs_dma; void* tx_ring_dma; void* rx_ring_dma; void* tx_ring; void* rx_ring; int /*<<< orphan*/ * tx_bufs; } ;
struct TYPE_2__ {struct device* parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct device {int dummy; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PKT_BUF_SZ ; 
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 void* dma_alloc_coherent (struct device*,int,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,void*,void*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct rhine_private* netdev_priv (struct net_device*) ; 
 int rqRhineI ; 

__attribute__((used)) static int alloc_ring(struct net_device* dev)
{
	struct rhine_private *rp = netdev_priv(dev);
	struct device *hwdev = dev->dev.parent;
	void *ring;
	dma_addr_t ring_dma;

	ring = dma_alloc_coherent(hwdev,
				  RX_RING_SIZE * sizeof(struct rx_desc) +
				  TX_RING_SIZE * sizeof(struct tx_desc),
				  &ring_dma,
				  GFP_ATOMIC);
	if (!ring) {
		netdev_err(dev, "Could not allocate DMA memory\n");
		return -ENOMEM;
	}
	if (rp->quirks & rqRhineI) {
		rp->tx_bufs = dma_alloc_coherent(hwdev,
						 PKT_BUF_SZ * TX_RING_SIZE,
						 &rp->tx_bufs_dma,
						 GFP_ATOMIC);
		if (rp->tx_bufs == NULL) {
			dma_free_coherent(hwdev,
					  RX_RING_SIZE * sizeof(struct rx_desc) +
					  TX_RING_SIZE * sizeof(struct tx_desc),
					  ring, ring_dma);
			return -ENOMEM;
		}
	}

	rp->rx_ring = ring;
	rp->tx_ring = ring + RX_RING_SIZE * sizeof(struct rx_desc);
	rp->rx_ring_dma = ring_dma;
	rp->tx_ring_dma = ring_dma + RX_RING_SIZE * sizeof(struct rx_desc);

	return 0;
}
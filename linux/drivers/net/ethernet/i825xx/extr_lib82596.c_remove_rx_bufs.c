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
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_2__ dev; } ;
struct i596_rbd {int /*<<< orphan*/ * skb; int /*<<< orphan*/  b_data; } ;
struct i596_private {TYPE_1__* dma; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {struct i596_rbd* rbds; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  PKT_BUF_SZ ; 
 scalar_t__ SWAP32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i596_private* netdev_priv (struct net_device*) ; 
 int rx_ring_size ; 

__attribute__((used)) static inline void remove_rx_bufs(struct net_device *dev)
{
	struct i596_private *lp = netdev_priv(dev);
	struct i596_rbd *rbd;
	int i;

	for (i = 0, rbd = lp->dma->rbds; i < rx_ring_size; i++, rbd++) {
		if (rbd->skb == NULL)
			break;
		dma_unmap_single(dev->dev.parent,
				 (dma_addr_t)SWAP32(rbd->b_data),
				 PKT_BUF_SZ, DMA_FROM_DEVICE);
		dev_kfree_skb(rbd->skb);
	}
}
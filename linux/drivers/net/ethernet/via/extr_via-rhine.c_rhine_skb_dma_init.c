#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rhine_skb_dma {TYPE_2__* skb; int /*<<< orphan*/  dma; } ;
struct rhine_private {int rx_buf_sz; } ;
struct TYPE_4__ {struct device* parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_2__*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 TYPE_2__* netdev_alloc_skb (struct net_device*,int const) ; 
 struct rhine_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct rhine_private*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int rhine_skb_dma_init(struct net_device *dev,
				     struct rhine_skb_dma *sd)
{
	struct rhine_private *rp = netdev_priv(dev);
	struct device *hwdev = dev->dev.parent;
	const int size = rp->rx_buf_sz;

	sd->skb = netdev_alloc_skb(dev, size);
	if (!sd->skb)
		return -ENOMEM;

	sd->dma = dma_map_single(hwdev, sd->skb->data, size, DMA_FROM_DEVICE);
	if (unlikely(dma_mapping_error(hwdev, sd->dma))) {
		netif_err(rp, drv, dev, "Rx DMA mapping failure\n");
		dev_kfree_skb_any(sd->skb);
		return -EIO;
	}

	return 0;
}
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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct ionic_rx_stats {int /*<<< orphan*/  dma_map_err; int /*<<< orphan*/  alloc_err; } ;
struct ionic_queue {int /*<<< orphan*/  name; struct ionic_lif* lif; } ;
struct ionic_lif {TYPE_1__* ionic; struct net_device* netdev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_warn_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,unsigned int) ; 
 struct ionic_rx_stats* q_to_rx_stats (struct ionic_queue*) ; 

__attribute__((used)) static struct sk_buff *ionic_rx_skb_alloc(struct ionic_queue *q, unsigned int len,
					  dma_addr_t *dma_addr)
{
	struct ionic_lif *lif = q->lif;
	struct ionic_rx_stats *stats;
	struct net_device *netdev;
	struct sk_buff *skb;
	struct device *dev;

	netdev = lif->netdev;
	dev = lif->ionic->dev;
	stats = q_to_rx_stats(q);
	skb = netdev_alloc_skb_ip_align(netdev, len);
	if (!skb) {
		net_warn_ratelimited("%s: SKB alloc failed on %s!\n",
				     netdev->name, q->name);
		stats->alloc_err++;
		return NULL;
	}

	*dma_addr = dma_map_single(dev, skb->data, len, DMA_FROM_DEVICE);
	if (dma_mapping_error(dev, *dma_addr)) {
		dev_kfree_skb(skb);
		net_warn_ratelimited("%s: DMA single map failed on %s!\n",
				     netdev->name, q->name);
		stats->dma_map_err++;
		return NULL;
	}

	return skb;
}
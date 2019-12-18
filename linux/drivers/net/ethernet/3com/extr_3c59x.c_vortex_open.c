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
struct vortex_private {int rx_ring_dma; struct sk_buff** rx_skbuff; TYPE_1__* rx_ring; int /*<<< orphan*/  gendev; scalar_t__ full_bus_master_rx; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct net_device {int irq; int /*<<< orphan*/  name; } ;
struct boom_rx_desc {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {void* next; void* addr; void* length; scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int LAST_FRAG ; 
 scalar_t__ NET_IP_ALIGN ; 
 int PKT_BUF_SZ ; 
 int RX_RING_SIZE ; 
 struct sk_buff* __netdev_alloc_skb (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_irq (int,struct net_device*) ; 
 struct vortex_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_emerg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  vortex_boomerang_interrupt ; 
 int vortex_debug ; 
 int vortex_up (struct net_device*) ; 

__attribute__((used)) static int
vortex_open(struct net_device *dev)
{
	struct vortex_private *vp = netdev_priv(dev);
	int i;
	int retval;
	dma_addr_t dma;

	/* Use the now-standard shared IRQ implementation. */
	if ((retval = request_irq(dev->irq, vortex_boomerang_interrupt, IRQF_SHARED, dev->name, dev))) {
		pr_err("%s: Could not reserve IRQ %d\n", dev->name, dev->irq);
		goto err;
	}

	if (vp->full_bus_master_rx) { /* Boomerang bus master. */
		if (vortex_debug > 2)
			pr_debug("%s:  Filling in the Rx ring.\n", dev->name);
		for (i = 0; i < RX_RING_SIZE; i++) {
			struct sk_buff *skb;
			vp->rx_ring[i].next = cpu_to_le32(vp->rx_ring_dma + sizeof(struct boom_rx_desc) * (i+1));
			vp->rx_ring[i].status = 0;	/* Clear complete bit. */
			vp->rx_ring[i].length = cpu_to_le32(PKT_BUF_SZ | LAST_FRAG);

			skb = __netdev_alloc_skb(dev, PKT_BUF_SZ + NET_IP_ALIGN,
						 GFP_KERNEL);
			vp->rx_skbuff[i] = skb;
			if (skb == NULL)
				break;			/* Bad news!  */

			skb_reserve(skb, NET_IP_ALIGN);	/* Align IP on 16 byte boundaries */
			dma = dma_map_single(vp->gendev, skb->data,
					     PKT_BUF_SZ, DMA_FROM_DEVICE);
			if (dma_mapping_error(vp->gendev, dma))
				break;
			vp->rx_ring[i].addr = cpu_to_le32(dma);
		}
		if (i != RX_RING_SIZE) {
			pr_emerg("%s: no memory for rx ring\n", dev->name);
			retval = -ENOMEM;
			goto err_free_skb;
		}
		/* Wrap the ring. */
		vp->rx_ring[i-1].next = cpu_to_le32(vp->rx_ring_dma);
	}

	retval = vortex_up(dev);
	if (!retval)
		goto out;

err_free_skb:
	for (i = 0; i < RX_RING_SIZE; i++) {
		if (vp->rx_skbuff[i]) {
			dev_kfree_skb(vp->rx_skbuff[i]);
			vp->rx_skbuff[i] = NULL;
		}
	}
	free_irq(dev->irq, dev);
err:
	if (vortex_debug > 1)
		pr_err("%s: vortex_open() fails: returning %d\n", dev->name, retval);
out:
	return retval;
}
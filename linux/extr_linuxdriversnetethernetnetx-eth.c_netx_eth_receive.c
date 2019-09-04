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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct netx_eth_priv {int /*<<< orphan*/  id; scalar_t__ sram_base; } ;
struct TYPE_2__ {unsigned int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_PTR_FIFO (int /*<<< orphan*/ ) ; 
 unsigned int FIFO_PTR_FRAMELEN_MASK ; 
 unsigned int FIFO_PTR_FRAMELEN_SHIFT ; 
 int FIFO_PTR_FRAMENO (unsigned int) ; 
 unsigned int FIFO_PTR_FRAMENO_MASK ; 
 unsigned int FIFO_PTR_FRAMENO_SHIFT ; 
 int FIFO_PTR_SEGMENT (unsigned int) ; 
 unsigned int FIFO_PTR_SEGMENT_MASK ; 
 unsigned int FIFO_PTR_SEGMENT_SHIFT ; 
 int /*<<< orphan*/  IND_FIFO_PORT_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  memcpy_fromio (unsigned char*,scalar_t__,unsigned int) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,unsigned int) ; 
 struct netx_eth_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 unsigned int pfifo_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfifo_push (int /*<<< orphan*/ ,int) ; 
 unsigned char* skb_put (struct sk_buff*,unsigned int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void netx_eth_receive(struct net_device *ndev)
{
	struct netx_eth_priv *priv = netdev_priv(ndev);
	unsigned int val, frameno, seg, len;
	unsigned char *data;
	struct sk_buff *skb;

	val = pfifo_pop(IND_FIFO_PORT_LO(priv->id));

	frameno = (val & FIFO_PTR_FRAMENO_MASK) >> FIFO_PTR_FRAMENO_SHIFT;
	seg = (val & FIFO_PTR_SEGMENT_MASK) >> FIFO_PTR_SEGMENT_SHIFT;
	len = (val & FIFO_PTR_FRAMELEN_MASK) >> FIFO_PTR_FRAMELEN_SHIFT;

	skb = netdev_alloc_skb(ndev, len);
	if (unlikely(skb == NULL)) {
		ndev->stats.rx_dropped++;
		return;
	}

	data = skb_put(skb, len);

	memcpy_fromio(data, priv->sram_base + frameno * 1560, len);

	pfifo_push(EMPTY_PTR_FIFO(priv->id),
		FIFO_PTR_SEGMENT(seg) | FIFO_PTR_FRAMENO(frameno));

	skb->protocol = eth_type_trans(skb, ndev);
	netif_rx(skb);
	ndev->stats.rx_packets++;
	ndev->stats.rx_bytes += len;
}
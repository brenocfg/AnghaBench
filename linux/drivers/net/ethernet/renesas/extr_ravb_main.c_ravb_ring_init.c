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
struct sk_buff {int dummy; } ;
struct ravb_tx_desc {int dummy; } ;
struct ravb_private {int num_tx_desc; int rx_buf_sz; int* num_rx_ring; int* num_tx_ring; void** tx_ring; int /*<<< orphan*/ * tx_desc_dma; scalar_t__* dirty_rx; void** rx_ring; int /*<<< orphan*/ * rx_desc_dma; int /*<<< orphan*/ * tx_align; struct sk_buff*** rx_skb; void** tx_skb; } ;
struct ravb_ex_rx_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {int mtu; TYPE_1__ dev; } ;
typedef  int /*<<< orphan*/  __sum16 ;

/* Variables and functions */
 int DPTR_ALIGN ; 
 int ENOMEM ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PKT_BUF_SZ ; 
 int RAVB_ALIGN ; 
 int VLAN_HLEN ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int) ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ravb_ring_free (struct net_device*,int) ; 
 int /*<<< orphan*/  ravb_set_buffer_align (struct sk_buff*) ; 

__attribute__((used)) static int ravb_ring_init(struct net_device *ndev, int q)
{
	struct ravb_private *priv = netdev_priv(ndev);
	int num_tx_desc = priv->num_tx_desc;
	struct sk_buff *skb;
	int ring_size;
	int i;

	priv->rx_buf_sz = (ndev->mtu <= 1492 ? PKT_BUF_SZ : ndev->mtu) +
		ETH_HLEN + VLAN_HLEN + sizeof(__sum16);

	/* Allocate RX and TX skb rings */
	priv->rx_skb[q] = kcalloc(priv->num_rx_ring[q],
				  sizeof(*priv->rx_skb[q]), GFP_KERNEL);
	priv->tx_skb[q] = kcalloc(priv->num_tx_ring[q],
				  sizeof(*priv->tx_skb[q]), GFP_KERNEL);
	if (!priv->rx_skb[q] || !priv->tx_skb[q])
		goto error;

	for (i = 0; i < priv->num_rx_ring[q]; i++) {
		skb = netdev_alloc_skb(ndev, priv->rx_buf_sz + RAVB_ALIGN - 1);
		if (!skb)
			goto error;
		ravb_set_buffer_align(skb);
		priv->rx_skb[q][i] = skb;
	}

	if (num_tx_desc > 1) {
		/* Allocate rings for the aligned buffers */
		priv->tx_align[q] = kmalloc(DPTR_ALIGN * priv->num_tx_ring[q] +
					    DPTR_ALIGN - 1, GFP_KERNEL);
		if (!priv->tx_align[q])
			goto error;
	}

	/* Allocate all RX descriptors. */
	ring_size = sizeof(struct ravb_ex_rx_desc) * (priv->num_rx_ring[q] + 1);
	priv->rx_ring[q] = dma_alloc_coherent(ndev->dev.parent, ring_size,
					      &priv->rx_desc_dma[q],
					      GFP_KERNEL);
	if (!priv->rx_ring[q])
		goto error;

	priv->dirty_rx[q] = 0;

	/* Allocate all TX descriptors. */
	ring_size = sizeof(struct ravb_tx_desc) *
		    (priv->num_tx_ring[q] * num_tx_desc + 1);
	priv->tx_ring[q] = dma_alloc_coherent(ndev->dev.parent, ring_size,
					      &priv->tx_desc_dma[q],
					      GFP_KERNEL);
	if (!priv->tx_ring[q])
		goto error;

	return 0;

error:
	ravb_ring_free(ndev, q);

	return -ENOMEM;
}
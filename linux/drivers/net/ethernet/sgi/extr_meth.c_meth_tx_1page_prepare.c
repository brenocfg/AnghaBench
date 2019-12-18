#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_4__* cat_buf; scalar_t__ dt; } ;
struct TYPE_7__ {int raw; } ;
struct TYPE_12__ {TYPE_5__ data; TYPE_1__ header; } ;
typedef  TYPE_6__ tx_packet ;
struct sk_buff {int len; scalar_t__ data; } ;
struct meth_private {size_t tx_write; TYPE_2__* pdev; TYPE_6__* tx_ring; } ;
typedef  int dma_addr_t ;
struct TYPE_9__ {int start_addr; int len; } ;
struct TYPE_10__ {TYPE_3__ form; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int METH_TX_CMD_INT_EN ; 
 int TX_CATBUF1 ; 
 int dma_map_single (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,scalar_t__,int) ; 

__attribute__((used)) static void meth_tx_1page_prepare(struct meth_private *priv,
				  struct sk_buff *skb)
{
	tx_packet *desc = &priv->tx_ring[priv->tx_write];
	void *buffer_data = (void *)(((unsigned long)skb->data + 7) & ~7);
	int unaligned_len = (int)((unsigned long)buffer_data - (unsigned long)skb->data);
	int buffer_len = skb->len - unaligned_len;
	dma_addr_t catbuf;

	desc->header.raw = METH_TX_CMD_INT_EN | TX_CATBUF1 | (skb->len - 1);

	/* unaligned part */
	if (unaligned_len) {
		skb_copy_from_linear_data(skb, desc->data.dt + (120 - unaligned_len),
			      unaligned_len);
		desc->header.raw |= (128 - unaligned_len) << 16;
	}

	/* first page */
	catbuf = dma_map_single(&priv->pdev->dev, buffer_data, buffer_len,
				DMA_TO_DEVICE);
	desc->data.cat_buf[0].form.start_addr = catbuf >> 3;
	desc->data.cat_buf[0].form.len = buffer_len - 1;
}
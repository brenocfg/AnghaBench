#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct sg_desc {TYPE_2__* frags; int /*<<< orphan*/  linear_len; int /*<<< orphan*/  linear_addr; } ;
struct TYPE_4__ {struct sg_desc* desc; } ;
struct hix5hd2_priv {int /*<<< orphan*/  dev; TYPE_1__ tx_ring; } ;
typedef  void* dma_addr_t ;
struct TYPE_6__ {int nr_frags; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void hix5hd2_clean_sg_desc(struct hix5hd2_priv *priv,
				  struct sk_buff *skb, u32 pos)
{
	struct sg_desc *desc;
	dma_addr_t addr;
	u32 len;
	int i;

	desc = priv->tx_ring.desc + pos;

	addr = le32_to_cpu(desc->linear_addr);
	len = le32_to_cpu(desc->linear_len);
	dma_unmap_single(priv->dev, addr, len, DMA_TO_DEVICE);

	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
		addr = le32_to_cpu(desc->frags[i].addr);
		len = le32_to_cpu(desc->frags[i].size);
		dma_unmap_page(priv->dev, addr, len, DMA_TO_DEVICE);
	}
}
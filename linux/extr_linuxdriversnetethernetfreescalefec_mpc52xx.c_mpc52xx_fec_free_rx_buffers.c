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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct bcom_task {int dummy; } ;
struct bcom_fec_bd {int /*<<< orphan*/  skb_pa; } ;
struct bcom_bd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  bcom_queue_empty (struct bcom_task*) ; 
 struct sk_buff* bcom_retrieve_buffer (struct bcom_task*,int /*<<< orphan*/ *,struct bcom_bd**) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static void mpc52xx_fec_free_rx_buffers(struct net_device *dev, struct bcom_task *s)
{
	while (!bcom_queue_empty(s)) {
		struct bcom_fec_bd *bd;
		struct sk_buff *skb;

		skb = bcom_retrieve_buffer(s, NULL, (struct bcom_bd **)&bd);
		dma_unmap_single(dev->dev.parent, bd->skb_pa, skb->len,
				 DMA_FROM_DEVICE);
		kfree_skb(skb);
	}
}
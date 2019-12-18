#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct hinic_rxq {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  rx_unmap_skb (struct hinic_rxq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rx_free_skb(struct hinic_rxq *rxq, struct sk_buff *skb,
			dma_addr_t dma_addr)
{
	rx_unmap_skb(rxq, dma_addr);
	dev_kfree_skb_any(skb);
}
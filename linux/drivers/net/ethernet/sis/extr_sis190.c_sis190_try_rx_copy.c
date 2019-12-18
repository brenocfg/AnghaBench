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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct sis190_private {int /*<<< orphan*/  rx_buf_sz; int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 struct sk_buff* netdev_alloc_skb_ip_align (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rx_copybreak ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool sis190_try_rx_copy(struct sis190_private *tp,
			       struct sk_buff **sk_buff, int pkt_size,
			       dma_addr_t addr)
{
	struct sk_buff *skb;
	bool done = false;

	if (pkt_size >= rx_copybreak)
		goto out;

	skb = netdev_alloc_skb_ip_align(tp->dev, pkt_size);
	if (!skb)
		goto out;

	pci_dma_sync_single_for_cpu(tp->pci_dev, addr, tp->rx_buf_sz,
				PCI_DMA_FROMDEVICE);
	skb_copy_to_linear_data(skb, sk_buff[0]->data, pkt_size);
	*sk_buff = skb;
	done = true;
out:
	return done;
}
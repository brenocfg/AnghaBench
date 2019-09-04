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
struct pcnet32_tx_head {int dummy; } ;
struct pcnet32_private {int tx_ring_size; int tx_mod_mask; unsigned int tx_len_bits; int /*<<< orphan*/  pci_dev; struct sk_buff** tx_skbuff; struct sk_buff** tx_dma_addr; struct sk_buff* tx_ring_dma_addr; struct pcnet32_tx_head* tx_ring; } ;
struct net_device {int dummy; } ;
typedef  struct sk_buff* dma_addr_t ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 void* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sk_buff**) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,struct pcnet32_tx_head*,struct sk_buff*) ; 
 struct pcnet32_tx_head* pci_zalloc_consistent (int /*<<< orphan*/ ,int,struct sk_buff**) ; 
 int /*<<< orphan*/  pcnet32_purge_tx_ring (struct net_device*) ; 

__attribute__((used)) static void pcnet32_realloc_tx_ring(struct net_device *dev,
				    struct pcnet32_private *lp,
				    unsigned int size)
{
	dma_addr_t new_ring_dma_addr;
	dma_addr_t *new_dma_addr_list;
	struct pcnet32_tx_head *new_tx_ring;
	struct sk_buff **new_skb_list;
	unsigned int entries = BIT(size);

	pcnet32_purge_tx_ring(dev);

	new_tx_ring =
		pci_zalloc_consistent(lp->pci_dev,
				      sizeof(struct pcnet32_tx_head) * entries,
				      &new_ring_dma_addr);
	if (new_tx_ring == NULL)
		return;

	new_dma_addr_list = kcalloc(entries, sizeof(dma_addr_t), GFP_ATOMIC);
	if (!new_dma_addr_list)
		goto free_new_tx_ring;

	new_skb_list = kcalloc(entries, sizeof(struct sk_buff *), GFP_ATOMIC);
	if (!new_skb_list)
		goto free_new_lists;

	kfree(lp->tx_skbuff);
	kfree(lp->tx_dma_addr);
	pci_free_consistent(lp->pci_dev,
			    sizeof(struct pcnet32_tx_head) * lp->tx_ring_size,
			    lp->tx_ring, lp->tx_ring_dma_addr);

	lp->tx_ring_size = entries;
	lp->tx_mod_mask = lp->tx_ring_size - 1;
	lp->tx_len_bits = (size << 12);
	lp->tx_ring = new_tx_ring;
	lp->tx_ring_dma_addr = new_ring_dma_addr;
	lp->tx_dma_addr = new_dma_addr_list;
	lp->tx_skbuff = new_skb_list;
	return;

free_new_lists:
	kfree(new_dma_addr_list);
free_new_tx_ring:
	pci_free_consistent(lp->pci_dev,
			    sizeof(struct pcnet32_tx_head) * entries,
			    new_tx_ring,
			    new_ring_dma_addr);
}
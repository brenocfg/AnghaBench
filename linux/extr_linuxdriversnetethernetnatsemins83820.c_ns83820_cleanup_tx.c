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
struct ns83820 {int /*<<< orphan*/ * tx_descs; int /*<<< orphan*/  nr_tx_skbs; int /*<<< orphan*/  pci_dev; struct sk_buff** tx_skbs; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int CMDSTS_LEN_MASK ; 
 int DESC_BUFPTR ; 
 size_t DESC_CMDSTS ; 
 unsigned int DESC_SIZE ; 
 unsigned int NR_TX_DESC ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  desc_addr_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ns83820_cleanup_tx(struct ns83820 *dev)
{
	unsigned i;

	for (i=0; i<NR_TX_DESC; i++) {
		struct sk_buff *skb = dev->tx_skbs[i];
		dev->tx_skbs[i] = NULL;
		if (skb) {
			__le32 *desc = dev->tx_descs + (i * DESC_SIZE);
			pci_unmap_single(dev->pci_dev,
					desc_addr_get(desc + DESC_BUFPTR),
					le32_to_cpu(desc[DESC_CMDSTS]) & CMDSTS_LEN_MASK,
					PCI_DMA_TODEVICE);
			dev_kfree_skb_irq(skb);
			atomic_dec(&dev->nr_tx_skbs);
		}
	}

	memset(dev->tx_descs, 0, NR_TX_DESC * DESC_SIZE * 4);
}
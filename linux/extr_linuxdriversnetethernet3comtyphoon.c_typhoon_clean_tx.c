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
typedef  scalar_t__ u32 ;
struct typhoon {int /*<<< orphan*/  pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  volatile addr; } ;
struct tx_desc {int flags; unsigned long tx_addr; int /*<<< orphan*/  len; TYPE_1__ frag; } ;
struct transmit_ring {scalar_t__ lastRead; scalar_t__ ringBase; } ;
struct sk_buff {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int TYPHOON_FRAG_DESC ; 
 int TYPHOON_TX_DESC ; 
 int TYPHOON_TYPE_MASK ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/  volatile) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typhoon_inc_tx_index (scalar_t__*,int) ; 

__attribute__((used)) static u32
typhoon_clean_tx(struct typhoon *tp, struct transmit_ring *txRing,
			volatile __le32 * index)
{
	u32 lastRead = txRing->lastRead;
	struct tx_desc *tx;
	dma_addr_t skb_dma;
	int dma_len;
	int type;

	while(lastRead != le32_to_cpu(*index)) {
		tx = (struct tx_desc *) (txRing->ringBase + lastRead);
		type = tx->flags & TYPHOON_TYPE_MASK;

		if(type == TYPHOON_TX_DESC) {
			/* This tx_desc describes a packet.
			 */
			unsigned long ptr = tx->tx_addr;
			struct sk_buff *skb = (struct sk_buff *) ptr;
			dev_kfree_skb_irq(skb);
		} else if(type == TYPHOON_FRAG_DESC) {
			/* This tx_desc describes a memory mapping. Free it.
			 */
			skb_dma = (dma_addr_t) le32_to_cpu(tx->frag.addr);
			dma_len = le16_to_cpu(tx->len);
			pci_unmap_single(tp->pdev, skb_dma, dma_len,
				       PCI_DMA_TODEVICE);
		}

		tx->flags = 0;
		typhoon_inc_tx_index(&lastRead, 1);
	}

	return lastRead;
}
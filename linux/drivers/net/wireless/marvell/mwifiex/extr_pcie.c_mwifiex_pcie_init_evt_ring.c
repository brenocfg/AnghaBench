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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct pcie_service_card {struct mwifiex_evt_buf_desc** evtbd_ring; scalar_t__ evtbd_ring_vbase; struct sk_buff** evt_buf_list; } ;
struct mwifiex_evt_buf_desc {scalar_t__ flags; scalar_t__ len; scalar_t__ paddr; } ;
struct mwifiex_adapter {struct pcie_service_card* card; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EVENT ; 
 int /*<<< orphan*/  MAX_EVENT_SIZE ; 
 int MWIFIEX_MAX_EVT_BD ; 
 scalar_t__ MWIFIEX_SKB_DMA_ADDR (struct sk_buff*) ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ mwifiex_map_pci_memory (struct mwifiex_adapter*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_pcie_init_evt_ring(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;
	struct mwifiex_evt_buf_desc *desc;
	struct sk_buff *skb;
	dma_addr_t buf_pa;
	int i;

	for (i = 0; i < MWIFIEX_MAX_EVT_BD; i++) {
		/* Allocate skb here so that firmware can DMA data from it */
		skb = dev_alloc_skb(MAX_EVENT_SIZE);
		if (!skb) {
			mwifiex_dbg(adapter, ERROR,
				    "Unable to allocate skb for EVENT buf.\n");
			kfree(card->evtbd_ring_vbase);
			return -ENOMEM;
		}
		skb_put(skb, MAX_EVENT_SIZE);

		if (mwifiex_map_pci_memory(adapter, skb, MAX_EVENT_SIZE,
					   PCI_DMA_FROMDEVICE))
			return -1;

		buf_pa = MWIFIEX_SKB_DMA_ADDR(skb);

		mwifiex_dbg(adapter, EVENT,
			    "info: EVT ring: skb=%p len=%d data=%p buf_pa=%#x:%x\n",
			    skb, skb->len, skb->data, (u32)buf_pa,
			    (u32)((u64)buf_pa >> 32));

		card->evt_buf_list[i] = skb;
		card->evtbd_ring[i] = (void *)(card->evtbd_ring_vbase +
				      (sizeof(*desc) * i));
		desc = card->evtbd_ring[i];
		desc->paddr = buf_pa;
		desc->len = (u16)skb->len;
		desc->flags = 0;
	}

	return 0;
}
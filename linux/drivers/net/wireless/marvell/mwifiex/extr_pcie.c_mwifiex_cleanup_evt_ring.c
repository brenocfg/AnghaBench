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
struct pcie_service_card {struct sk_buff** evt_buf_list; struct mwifiex_evt_buf_desc** evtbd_ring; } ;
struct mwifiex_evt_buf_desc {int dummy; } ;
struct mwifiex_adapter {struct pcie_service_card* card; } ;

/* Variables and functions */
 int MWIFIEX_MAX_EVT_BD ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct mwifiex_evt_buf_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mwifiex_unmap_pci_memory (struct mwifiex_adapter*,struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mwifiex_cleanup_evt_ring(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;
	struct mwifiex_evt_buf_desc *desc;
	struct sk_buff *skb;
	int i;

	for (i = 0; i < MWIFIEX_MAX_EVT_BD; i++) {
		desc = card->evtbd_ring[i];
		if (card->evt_buf_list[i]) {
			skb = card->evt_buf_list[i];
			mwifiex_unmap_pci_memory(adapter, skb,
						 PCI_DMA_FROMDEVICE);
			dev_kfree_skb_any(skb);
		}
		card->evt_buf_list[i] = NULL;
		memset(desc, 0, sizeof(*desc));
	}

	return;
}
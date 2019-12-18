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
struct pcie_service_card {int /*<<< orphan*/  dev; } ;
struct mwifiex_dma_mapping {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct mwifiex_adapter {struct pcie_service_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  mwifiex_get_mapping (struct sk_buff*,struct mwifiex_dma_mapping*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mwifiex_unmap_pci_memory(struct mwifiex_adapter *adapter,
				     struct sk_buff *skb, int flags)
{
	struct pcie_service_card *card = adapter->card;
	struct mwifiex_dma_mapping mapping;

	mwifiex_get_mapping(skb, &mapping);
	pci_unmap_single(card->dev, mapping.addr, mapping.len, flags);
}
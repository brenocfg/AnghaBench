#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rx {scalar_t__ skb; int /*<<< orphan*/  dma_addr; } ;
struct TYPE_3__ {unsigned int count; } ;
struct TYPE_4__ {TYPE_1__ rfds; } ;
struct nic {int /*<<< orphan*/ * rx_to_clean; int /*<<< orphan*/  rx_to_use; struct rx* rxs; int /*<<< orphan*/  pdev; int /*<<< orphan*/  ru_running; TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  RFD_BUF_LEN ; 
 int /*<<< orphan*/  RU_UNINITIALIZED ; 
 int /*<<< orphan*/  dev_kfree_skb (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct rx*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e100_rx_clean_list(struct nic *nic)
{
	struct rx *rx;
	unsigned int i, count = nic->params.rfds.count;

	nic->ru_running = RU_UNINITIALIZED;

	if (nic->rxs) {
		for (rx = nic->rxs, i = 0; i < count; rx++, i++) {
			if (rx->skb) {
				pci_unmap_single(nic->pdev, rx->dma_addr,
					RFD_BUF_LEN, PCI_DMA_BIDIRECTIONAL);
				dev_kfree_skb(rx->skb);
			}
		}
		kfree(nic->rxs);
		nic->rxs = NULL;
	}

	nic->rx_to_use = nic->rx_to_clean = NULL;
}
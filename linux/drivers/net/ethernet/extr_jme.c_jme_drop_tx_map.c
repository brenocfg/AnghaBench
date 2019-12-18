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
struct jme_ring {struct jme_buffer_info* bufinf; } ;
struct jme_buffer_info {scalar_t__ len; scalar_t__ mapping; } ;
struct jme_adapter {int tx_ring_mask; int /*<<< orphan*/  pdev; struct jme_ring* txring; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jme_drop_tx_map(struct jme_adapter *jme, int startidx, int count)
{
	struct jme_ring *txring = &(jme->txring[0]);
	struct jme_buffer_info *txbi = txring->bufinf, *ctxbi;
	int mask = jme->tx_ring_mask;
	int j;

	for (j = 0 ; j < count ; j++) {
		ctxbi = txbi + ((startidx + j + 2) & (mask));
		pci_unmap_page(jme->pdev,
				ctxbi->mapping,
				ctxbi->len,
				PCI_DMA_TODEVICE);

		ctxbi->mapping = 0;
		ctxbi->len = 0;
	}
}
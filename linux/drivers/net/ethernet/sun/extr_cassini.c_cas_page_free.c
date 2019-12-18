#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cas {int /*<<< orphan*/  page_order; int /*<<< orphan*/  page_size; int /*<<< orphan*/  pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  dma_addr; } ;
typedef  TYPE_1__ cas_page_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cas_page_free(struct cas *cp, cas_page_t *page)
{
	pci_unmap_page(cp->pdev, page->dma_addr, cp->page_size,
		       PCI_DMA_FROMDEVICE);
	__free_pages(page->buffer, cp->page_order);
	kfree(page);
	return 0;
}
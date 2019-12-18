#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct cas {int /*<<< orphan*/  page_size; int /*<<< orphan*/  pdev; int /*<<< orphan*/  page_order; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_6__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  list; } ;
typedef  TYPE_1__ cas_page_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  RX_USED_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_pages (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  pci_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static cas_page_t *cas_page_alloc(struct cas *cp, const gfp_t flags)
{
	cas_page_t *page;

	page = kmalloc(sizeof(cas_page_t), flags);
	if (!page)
		return NULL;

	INIT_LIST_HEAD(&page->list);
	RX_USED_SET(page, 0);
	page->buffer = alloc_pages(flags, cp->page_order);
	if (!page->buffer)
		goto page_err;
	page->dma_addr = pci_map_page(cp->pdev, page->buffer, 0,
				      cp->page_size, PCI_DMA_FROMDEVICE);
	return page;

page_err:
	kfree(page);
	return NULL;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct page {int /*<<< orphan*/ * mapping; } ;
struct TYPE_5__ {int /*<<< orphan*/  sgl; } ;
struct msc {unsigned long nr_pages; scalar_t__ base; TYPE_2__ single_sgt; } ;
struct TYPE_6__ {TYPE_1__* parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* msc_dev (struct msc*) ; 
 int /*<<< orphan*/  sg_free_table (TYPE_2__*) ; 
 struct page* virt_to_page (scalar_t__) ; 

__attribute__((used)) static void msc_buffer_contig_free(struct msc *msc)
{
	unsigned long off;

	dma_unmap_sg(msc_dev(msc)->parent->parent, msc->single_sgt.sgl,
		     1, DMA_FROM_DEVICE);
	sg_free_table(&msc->single_sgt);

	for (off = 0; off < msc->nr_pages << PAGE_SHIFT; off += PAGE_SIZE) {
		struct page *page = virt_to_page(msc->base + off);

		page->mapping = NULL;
		__free_page(page);
	}

	msc->nr_pages = 0;
}
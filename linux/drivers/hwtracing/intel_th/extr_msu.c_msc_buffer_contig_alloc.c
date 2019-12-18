#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  sgl; } ;
struct msc {unsigned long nr_pages; TYPE_2__ single_sgt; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  base; } ;
struct TYPE_7__ {TYPE_1__* parent; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int GFP_DMA32 ; 
 int GFP_KERNEL ; 
 unsigned long PAGE_SHIFT ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __free_pages (struct page*,unsigned int) ; 
 struct page* alloc_pages (int,unsigned int) ; 
 int dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 unsigned int get_order (unsigned long) ; 
 TYPE_4__* msc_dev (struct msc*) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int sg_alloc_table (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_free_table (TYPE_2__*) ; 
 int /*<<< orphan*/  sg_set_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  split_page (struct page*,unsigned int) ; 

__attribute__((used)) static int msc_buffer_contig_alloc(struct msc *msc, unsigned long size)
{
	unsigned long nr_pages = size >> PAGE_SHIFT;
	unsigned int order = get_order(size);
	struct page *page;
	int ret;

	if (!size)
		return 0;

	ret = sg_alloc_table(&msc->single_sgt, 1, GFP_KERNEL);
	if (ret)
		goto err_out;

	ret = -ENOMEM;
	page = alloc_pages(GFP_KERNEL | __GFP_ZERO | GFP_DMA32, order);
	if (!page)
		goto err_free_sgt;

	split_page(page, order);
	sg_set_buf(msc->single_sgt.sgl, page_address(page), size);

	ret = dma_map_sg(msc_dev(msc)->parent->parent, msc->single_sgt.sgl, 1,
			 DMA_FROM_DEVICE);
	if (ret < 0)
		goto err_free_pages;

	msc->nr_pages = nr_pages;
	msc->base = page_address(page);
	msc->base_addr = sg_dma_address(msc->single_sgt.sgl);

	return 0;

err_free_pages:
	__free_pages(page, order);

err_free_sgt:
	sg_free_table(&msc->single_sgt);

err_out:
	return ret;
}
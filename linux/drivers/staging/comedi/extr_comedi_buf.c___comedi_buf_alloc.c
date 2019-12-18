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
struct page {int dummy; } ;
struct comedi_subdevice {scalar_t__ async_dma_dir; int /*<<< orphan*/  spin_lock; struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; } ;
struct comedi_buf_page {int /*<<< orphan*/  virt_addr; } ;
struct comedi_buf_map {scalar_t__ dma_dir; struct comedi_buf_page* page_list; } ;
struct comedi_async {int /*<<< orphan*/  prealloc_buf; struct comedi_buf_map* buf_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_PAGE_PROTECTION ; 
 int /*<<< orphan*/  CONFIG_HAS_DMA ; 
 scalar_t__ DMA_NONE ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_MAP ; 
 struct comedi_buf_map* comedi_buf_map_alloc (struct comedi_device*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vfree (struct page**) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 
 struct page** vmalloc (int) ; 
 int /*<<< orphan*/  vmap (struct page**,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __comedi_buf_alloc(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       unsigned int n_pages)
{
	struct comedi_async *async = s->async;
	struct page **pages = NULL;
	struct comedi_buf_map *bm;
	struct comedi_buf_page *buf;
	unsigned long flags;
	unsigned int i;

	if (!IS_ENABLED(CONFIG_HAS_DMA) && s->async_dma_dir != DMA_NONE) {
		dev_err(dev->class_dev,
			"dma buffer allocation not supported\n");
		return;
	}

	bm = comedi_buf_map_alloc(dev, s->async_dma_dir, n_pages);
	if (!bm)
		return;

	spin_lock_irqsave(&s->spin_lock, flags);
	async->buf_map = bm;
	spin_unlock_irqrestore(&s->spin_lock, flags);

	if (bm->dma_dir != DMA_NONE) {
		/*
		 * DMA buffer was allocated as a single block.
		 * Address is in page_list[0].
		 */
		buf = &bm->page_list[0];
		async->prealloc_buf = buf->virt_addr;
	} else {
		pages = vmalloc(sizeof(struct page *) * n_pages);
		if (!pages)
			return;

		for (i = 0; i < n_pages; i++) {
			buf = &bm->page_list[i];
			pages[i] = virt_to_page(buf->virt_addr);
		}

		/* vmap the pages to prealloc_buf */
		async->prealloc_buf = vmap(pages, n_pages, VM_MAP,
					   COMEDI_PAGE_PROTECTION);

		vfree(pages);
	}
}
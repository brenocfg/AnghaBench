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
struct saa7134_dmasound {int nr_pages; int /*<<< orphan*/ * vaddr; int /*<<< orphan*/ * sglist; } ;
struct saa7134_dev {struct saa7134_dmasound dmasound; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  array_size (int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sg_set_page (int /*<<< orphan*/ *,struct page*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vmalloc_32 (int) ; 
 struct page* vmalloc_to_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vzalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int saa7134_alsa_dma_init(struct saa7134_dev *dev, int nr_pages)
{
	struct saa7134_dmasound *dma = &dev->dmasound;
	struct page *pg;
	int i;

	dma->vaddr = vmalloc_32(nr_pages << PAGE_SHIFT);
	if (NULL == dma->vaddr) {
		pr_debug("vmalloc_32(%d pages) failed\n", nr_pages);
		return -ENOMEM;
	}

	pr_debug("vmalloc is at addr %p, size=%d\n",
		 dma->vaddr, nr_pages << PAGE_SHIFT);

	memset(dma->vaddr, 0, nr_pages << PAGE_SHIFT);
	dma->nr_pages = nr_pages;

	dma->sglist = vzalloc(array_size(sizeof(*dma->sglist), dma->nr_pages));
	if (NULL == dma->sglist)
		goto vzalloc_err;

	sg_init_table(dma->sglist, dma->nr_pages);
	for (i = 0; i < dma->nr_pages; i++) {
		pg = vmalloc_to_page(dma->vaddr + i * PAGE_SIZE);
		if (NULL == pg)
			goto vmalloc_to_page_err;
		sg_set_page(&dma->sglist[i], pg, PAGE_SIZE, 0);
	}
	return 0;

vmalloc_to_page_err:
	vfree(dma->sglist);
	dma->sglist = NULL;
vzalloc_err:
	vfree(dma->vaddr);
	dma->vaddr = NULL;
	return -ENOMEM;
}
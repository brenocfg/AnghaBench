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
struct videobuf_dmabuf {int direction; int nr_pages; int /*<<< orphan*/ * vaddr_pages; int /*<<< orphan*/ * dma_addr; int /*<<< orphan*/  dev; int /*<<< orphan*/ * vaddr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int VM_IOREMAP ; 
 int VM_MAP ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int,char*,int,...) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 
 int /*<<< orphan*/ * vmap (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int videobuf_dma_init_kernel(struct videobuf_dmabuf *dma, int direction,
			     int nr_pages)
{
	int i;

	dprintk(1, "init kernel [%d pages]\n", nr_pages);

	dma->direction = direction;
	dma->vaddr_pages = kcalloc(nr_pages, sizeof(*dma->vaddr_pages),
				   GFP_KERNEL);
	if (!dma->vaddr_pages)
		return -ENOMEM;

	dma->dma_addr = kcalloc(nr_pages, sizeof(*dma->dma_addr), GFP_KERNEL);
	if (!dma->dma_addr) {
		kfree(dma->vaddr_pages);
		return -ENOMEM;
	}
	for (i = 0; i < nr_pages; i++) {
		void *addr;

		addr = dma_alloc_coherent(dma->dev, PAGE_SIZE,
					  &(dma->dma_addr[i]), GFP_KERNEL);
		if (addr == NULL)
			goto out_free_pages;

		dma->vaddr_pages[i] = virt_to_page(addr);
	}
	dma->vaddr = vmap(dma->vaddr_pages, nr_pages, VM_MAP | VM_IOREMAP,
			  PAGE_KERNEL);
	if (NULL == dma->vaddr) {
		dprintk(1, "vmalloc_32(%d pages) failed\n", nr_pages);
		goto out_free_pages;
	}

	dprintk(1, "vmalloc is at addr %p, size=%d\n",
		dma->vaddr, nr_pages << PAGE_SHIFT);

	memset(dma->vaddr, 0, nr_pages << PAGE_SHIFT);
	dma->nr_pages = nr_pages;

	return 0;
out_free_pages:
	while (i > 0) {
		void *addr;

		i--;
		addr = page_address(dma->vaddr_pages[i]);
		dma_free_coherent(dma->dev, PAGE_SIZE, addr, dma->dma_addr[i]);
	}
	kfree(dma->dma_addr);
	dma->dma_addr = NULL;
	kfree(dma->vaddr_pages);
	dma->vaddr_pages = NULL;

	return -ENOMEM;

}
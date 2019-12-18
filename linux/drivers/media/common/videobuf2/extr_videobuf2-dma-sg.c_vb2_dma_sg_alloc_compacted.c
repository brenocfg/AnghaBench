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
struct vb2_dma_sg_buf {unsigned long size; struct page** pages; } ;
struct page {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int __GFP_NOWARN ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_pages (int,int) ; 
 int get_order (unsigned long) ; 
 int /*<<< orphan*/  split_page (struct page*,int) ; 

__attribute__((used)) static int vb2_dma_sg_alloc_compacted(struct vb2_dma_sg_buf *buf,
		gfp_t gfp_flags)
{
	unsigned int last_page = 0;
	unsigned long size = buf->size;

	while (size > 0) {
		struct page *pages;
		int order;
		int i;

		order = get_order(size);
		/* Don't over allocate*/
		if ((PAGE_SIZE << order) > size)
			order--;

		pages = NULL;
		while (!pages) {
			pages = alloc_pages(GFP_KERNEL | __GFP_ZERO |
					__GFP_NOWARN | gfp_flags, order);
			if (pages)
				break;

			if (order == 0) {
				while (last_page--)
					__free_page(buf->pages[last_page]);
				return -ENOMEM;
			}
			order--;
		}

		split_page(pages, order);
		for (i = 0; i < (1 << order); i++)
			buf->pages[last_page++] = &pages[i];

		size -= PAGE_SIZE << order;
	}

	return 0;
}
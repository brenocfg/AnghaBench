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
struct scatterlist {int dummy; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SIZE ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,int) ; 
 struct page* alloc_pages_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_alloc_icm_pages(struct scatterlist *mem, int order,
				gfp_t gfp_mask, int node)
{
	struct page *page;

	page = alloc_pages_node(node, gfp_mask, order);
	if (!page) {
		page = alloc_pages(gfp_mask, order);
		if (!page)
			return -ENOMEM;
	}

	sg_set_page(mem, page, PAGE_SIZE << order, 0);
	return 0;
}
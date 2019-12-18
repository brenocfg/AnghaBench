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
typedef  int phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 struct scatterlist* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct page* pfn_to_page (int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct scatterlist *
scif_p2p_setsg(phys_addr_t pa, int page_size, int page_cnt)
{
	struct scatterlist *sg;
	struct page *page;
	int i;

	sg = kcalloc(page_cnt, sizeof(struct scatterlist), GFP_KERNEL);
	if (!sg)
		return NULL;
	sg_init_table(sg, page_cnt);
	for (i = 0; i < page_cnt; i++) {
		page = pfn_to_page(pa >> PAGE_SHIFT);
		sg_set_page(&sg[i], page, page_size, 0);
		pa += page_size;
	}
	return sg;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct mmc_test_mem {size_t cnt; TYPE_1__* arr; } ;
typedef  int gfp_t ;
struct TYPE_2__ {unsigned int order; struct page* page; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned int,int /*<<< orphan*/ ) ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 struct page* alloc_pages (int,unsigned int) ; 
 unsigned int get_order (unsigned long) ; 
 TYPE_1__* kcalloc (unsigned int,int,int) ; 
 struct mmc_test_mem* kzalloc (int,int) ; 
 int /*<<< orphan*/  mmc_test_free_mem (struct mmc_test_mem*) ; 
 int nr_free_buffer_pages () ; 

__attribute__((used)) static struct mmc_test_mem *mmc_test_alloc_mem(unsigned long min_sz,
					       unsigned long max_sz,
					       unsigned int max_segs,
					       unsigned int max_seg_sz)
{
	unsigned long max_page_cnt = DIV_ROUND_UP(max_sz, PAGE_SIZE);
	unsigned long min_page_cnt = DIV_ROUND_UP(min_sz, PAGE_SIZE);
	unsigned long max_seg_page_cnt = DIV_ROUND_UP(max_seg_sz, PAGE_SIZE);
	unsigned long page_cnt = 0;
	unsigned long limit = nr_free_buffer_pages() >> 4;
	struct mmc_test_mem *mem;

	if (max_page_cnt > limit)
		max_page_cnt = limit;
	if (min_page_cnt > max_page_cnt)
		min_page_cnt = max_page_cnt;

	if (max_seg_page_cnt > max_page_cnt)
		max_seg_page_cnt = max_page_cnt;

	if (max_segs > max_page_cnt)
		max_segs = max_page_cnt;

	mem = kzalloc(sizeof(*mem), GFP_KERNEL);
	if (!mem)
		return NULL;

	mem->arr = kcalloc(max_segs, sizeof(*mem->arr), GFP_KERNEL);
	if (!mem->arr)
		goto out_free;

	while (max_page_cnt) {
		struct page *page;
		unsigned int order;
		gfp_t flags = GFP_KERNEL | GFP_DMA | __GFP_NOWARN |
				__GFP_NORETRY;

		order = get_order(max_seg_page_cnt << PAGE_SHIFT);
		while (1) {
			page = alloc_pages(flags, order);
			if (page || !order)
				break;
			order -= 1;
		}
		if (!page) {
			if (page_cnt < min_page_cnt)
				goto out_free;
			break;
		}
		mem->arr[mem->cnt].page = page;
		mem->arr[mem->cnt].order = order;
		mem->cnt += 1;
		if (max_page_cnt <= (1UL << order))
			break;
		max_page_cnt -= 1UL << order;
		page_cnt += 1UL << order;
		if (mem->cnt >= max_segs) {
			if (page_cnt < min_page_cnt)
				goto out_free;
			break;
		}
	}

	return mem;

out_free:
	mmc_test_free_mem(mem);
	return NULL;
}
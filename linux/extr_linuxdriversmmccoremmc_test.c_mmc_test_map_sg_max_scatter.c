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
struct scatterlist {int dummy; } ;
struct mmc_test_mem {unsigned int cnt; TYPE_1__* arr; } ;
struct TYPE_2__ {int order; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int PAGE_SIZE ; 
 void* page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,unsigned int) ; 
 int /*<<< orphan*/  sg_mark_end (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 

__attribute__((used)) static int mmc_test_map_sg_max_scatter(struct mmc_test_mem *mem,
				       unsigned long sz,
				       struct scatterlist *sglist,
				       unsigned int max_segs,
				       unsigned int max_seg_sz,
				       unsigned int *sg_len)
{
	struct scatterlist *sg = NULL;
	unsigned int i = mem->cnt, cnt;
	unsigned long len;
	void *base, *addr, *last_addr = NULL;

	sg_init_table(sglist, max_segs);

	*sg_len = 0;
	while (sz) {
		base = page_address(mem->arr[--i].page);
		cnt = 1 << mem->arr[i].order;
		while (sz && cnt) {
			addr = base + PAGE_SIZE * --cnt;
			if (last_addr && last_addr + PAGE_SIZE == addr)
				continue;
			last_addr = addr;
			len = PAGE_SIZE;
			if (len > max_seg_sz)
				len = max_seg_sz;
			if (len > sz)
				len = sz;
			if (sg)
				sg = sg_next(sg);
			else
				sg = sglist;
			if (!sg)
				return -EINVAL;
			sg_set_page(sg, virt_to_page(addr), len, 0);
			sz -= len;
			*sg_len += 1;
		}
		if (i == 0)
			i = mem->cnt;
	}

	if (sg)
		sg_mark_end(sg);

	return 0;
}
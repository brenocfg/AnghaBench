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
struct TYPE_2__ {unsigned long order; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,int) ; 
 int EINVAL ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,unsigned int) ; 
 int /*<<< orphan*/  sg_mark_end (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_test_map_sg(struct mmc_test_mem *mem, unsigned long size,
			   struct scatterlist *sglist, int repeat,
			   unsigned int max_segs, unsigned int max_seg_sz,
			   unsigned int *sg_len, int min_sg_len)
{
	struct scatterlist *sg = NULL;
	unsigned int i;
	unsigned long sz = size;

	sg_init_table(sglist, max_segs);
	if (min_sg_len > max_segs)
		min_sg_len = max_segs;

	*sg_len = 0;
	do {
		for (i = 0; i < mem->cnt; i++) {
			unsigned long len = PAGE_SIZE << mem->arr[i].order;

			if (min_sg_len && (size / min_sg_len < len))
				len = ALIGN(size / min_sg_len, 512);
			if (len > sz)
				len = sz;
			if (len > max_seg_sz)
				len = max_seg_sz;
			if (sg)
				sg = sg_next(sg);
			else
				sg = sglist;
			if (!sg)
				return -EINVAL;
			sg_set_page(sg, mem->arr[i].page, len, 0);
			sz -= len;
			*sg_len += 1;
			if (!sz)
				break;
		}
	} while (sz && repeat);

	if (sz)
		return -EINVAL;

	if (sg)
		sg_mark_end(sg);

	return 0;
}
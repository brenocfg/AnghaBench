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
typedef  int /*<<< orphan*/  u64 ;
struct scatterlist {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 struct scatterlist* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,int,int /*<<< orphan*/ ) ; 
 struct page* vmalloc_to_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct scatterlist *efa_vmalloc_buf_to_sg(u64 *buf, int page_cnt)
{
	struct scatterlist *sglist;
	struct page *pg;
	int i;

	sglist = kcalloc(page_cnt, sizeof(*sglist), GFP_KERNEL);
	if (!sglist)
		return NULL;
	sg_init_table(sglist, page_cnt);
	for (i = 0; i < page_cnt; i++) {
		pg = vmalloc_to_page(buf);
		if (!pg)
			goto err;
		sg_set_page(&sglist[i], pg, PAGE_SIZE, 0);
		buf += PAGE_SIZE / sizeof(*buf);
	}
	return sglist;

err:
	kfree(sglist);
	return NULL;
}
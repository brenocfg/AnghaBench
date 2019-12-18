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
struct hns_roce_buf_region {int /*<<< orphan*/  count; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  hns_roce_free_buf_list (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ * kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int hns_roce_alloc_buf_list(struct hns_roce_buf_region *regions,
			    dma_addr_t **bufs, int region_cnt)
{
	struct hns_roce_buf_region *r;
	int i;

	for (i = 0; i < region_cnt; i++) {
		r = &regions[i];
		bufs[i] = kcalloc(r->count, sizeof(dma_addr_t), GFP_KERNEL);
		if (!bufs[i])
			goto err_alloc;
	}

	return 0;

err_alloc:
	hns_roce_free_buf_list(bufs, i);

	return -ENOMEM;
}
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
struct sg_table {int /*<<< orphan*/  sgl; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_ALIGN (size_t) ; 
 int sg_alloc_table (struct sg_table*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_set_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __swiotlb_get_sgtable_page(struct sg_table *sgt,
				      struct page *page, size_t size)
{
	int ret = sg_alloc_table(sgt, 1, GFP_KERNEL);

	if (!ret)
		sg_set_page(sgt->sgl, page, PAGE_ALIGN(size), 0);

	return ret;
}
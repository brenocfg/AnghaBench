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
struct sg_table {int dummy; } ;
struct page {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int __swiotlb_get_sgtable_page (struct sg_table*,struct page*,size_t) ; 
 int /*<<< orphan*/  dma_to_phys (struct device*,int /*<<< orphan*/ ) ; 
 struct page* phys_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __swiotlb_get_sgtable(struct device *dev, struct sg_table *sgt,
				 void *cpu_addr, dma_addr_t handle, size_t size,
				 unsigned long attrs)
{
	struct page *page = phys_to_page(dma_to_phys(dev, handle));

	return __swiotlb_get_sgtable_page(sgt, page, size);
}
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
struct page {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int DMA_TO_DEVICE ; 
 int EFAULT ; 
 int /*<<< orphan*/  FOLL_WRITE ; 
 unsigned long PAGE_MASK ; 
 unsigned long __pa (unsigned long) ; 
 int get_user_pages_fast (unsigned long,int,int /*<<< orphan*/ ,struct page**) ; 
 int iommu_tce_direction (unsigned long) ; 
 scalar_t__ page_address (struct page*) ; 

__attribute__((used)) static int tce_iommu_use_page(unsigned long tce, unsigned long *hpa)
{
	struct page *page = NULL;
	enum dma_data_direction direction = iommu_tce_direction(tce);

	if (get_user_pages_fast(tce & PAGE_MASK, 1,
			direction != DMA_TO_DEVICE ? FOLL_WRITE : 0,
			&page) != 1)
		return -EFAULT;

	*hpa = __pa((unsigned long) page_address(page));

	return 0;
}
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
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int dma_addr_t ;

/* Variables and functions */
 unsigned long DMA_ATTR_SKIP_CPU_SYNC ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  __dma_page_dev_to_cpu (int /*<<< orphan*/ ,int,size_t,int) ; 
 int /*<<< orphan*/  dma_to_pfn (struct device*,int) ; 
 int /*<<< orphan*/  pfn_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arm_dma_unmap_page(struct device *dev, dma_addr_t handle,
		size_t size, enum dma_data_direction dir, unsigned long attrs)
{
	if ((attrs & DMA_ATTR_SKIP_CPU_SYNC) == 0)
		__dma_page_dev_to_cpu(pfn_to_page(dma_to_pfn(dev, handle)),
				      handle & ~PAGE_MASK, size, dir);
}
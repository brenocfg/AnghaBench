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
struct device {int dummy; } ;
typedef  scalar_t__ phys_addr_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned long DMA_ATTR_SKIP_CPU_SYNC ; 
 int /*<<< orphan*/  arch_sync_dma_for_device (struct device*,scalar_t__,size_t,int) ; 
 scalar_t__ page_to_phys (struct page*) ; 
 int /*<<< orphan*/  vdma_alloc (scalar_t__,size_t) ; 

__attribute__((used)) static dma_addr_t jazz_dma_map_page(struct device *dev, struct page *page,
		unsigned long offset, size_t size, enum dma_data_direction dir,
		unsigned long attrs)
{
	phys_addr_t phys = page_to_phys(page) + offset;

	if (!(attrs & DMA_ATTR_SKIP_CPU_SYNC))
		arch_sync_dma_for_device(dev, phys, size, dir);
	return vdma_alloc(phys, size);
}
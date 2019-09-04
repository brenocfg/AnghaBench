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
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned long DMA_ATTR_SKIP_CPU_SYNC ; 
 int /*<<< orphan*/  __xen_dma_page_cpu_to_dev (struct device*,int /*<<< orphan*/ ,size_t,int) ; 
 scalar_t__ is_device_dma_coherent (struct device*) ; 

void __xen_dma_map_page(struct device *hwdev, struct page *page,
	     dma_addr_t dev_addr, unsigned long offset, size_t size,
	     enum dma_data_direction dir, unsigned long attrs)
{
	if (is_device_dma_coherent(hwdev))
		return;
	if (attrs & DMA_ATTR_SKIP_CPU_SYNC)
		return;

	__xen_dma_page_cpu_to_dev(hwdev, dev_addr, size, dir);
}
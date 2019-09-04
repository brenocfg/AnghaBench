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
 int /*<<< orphan*/  DMA_MAP ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  dma_cache_maint (int,int,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __xen_dma_page_cpu_to_dev(struct device *hwdev, dma_addr_t handle,
		size_t size, enum dma_data_direction dir)
{
	dma_cache_maint(handle & PAGE_MASK, handle & ~PAGE_MASK, size, dir, DMA_MAP);
}
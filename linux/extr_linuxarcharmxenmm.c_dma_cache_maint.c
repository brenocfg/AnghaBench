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
struct TYPE_2__ {unsigned long dev_bus_addr; } ;
struct gnttab_cache_flush {unsigned long offset; size_t length; void* op; TYPE_1__ a; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  enum dma_cache_op { ____Placeholder_dma_cache_op } dma_cache_op ;
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 int DMA_MAP ; 
 int DMA_TO_DEVICE ; 
 int DMA_UNMAP ; 
 int /*<<< orphan*/  GNTTABOP_cache_flush ; 
 void* GNTTAB_CACHE_CLEAN ; 
 void* GNTTAB_CACHE_INVAL ; 
 int /*<<< orphan*/  HYPERVISOR_grant_table_op (int /*<<< orphan*/ ,struct gnttab_cache_flush*,int) ; 
 unsigned long XEN_PAGE_SHIFT ; 
 unsigned long XEN_PAGE_SIZE ; 

__attribute__((used)) static void dma_cache_maint(dma_addr_t handle, unsigned long offset,
	size_t size, enum dma_data_direction dir, enum dma_cache_op op)
{
	struct gnttab_cache_flush cflush;
	unsigned long xen_pfn;
	size_t left = size;

	xen_pfn = (handle >> XEN_PAGE_SHIFT) + offset / XEN_PAGE_SIZE;
	offset %= XEN_PAGE_SIZE;

	do {
		size_t len = left;
	
		/* buffers in highmem or foreign pages cannot cross page
		 * boundaries */
		if (len + offset > XEN_PAGE_SIZE)
			len = XEN_PAGE_SIZE - offset;

		cflush.op = 0;
		cflush.a.dev_bus_addr = xen_pfn << XEN_PAGE_SHIFT;
		cflush.offset = offset;
		cflush.length = len;

		if (op == DMA_UNMAP && dir != DMA_TO_DEVICE)
			cflush.op = GNTTAB_CACHE_INVAL;
		if (op == DMA_MAP) {
			if (dir == DMA_FROM_DEVICE)
				cflush.op = GNTTAB_CACHE_INVAL;
			else
				cflush.op = GNTTAB_CACHE_CLEAN;
		}
		if (cflush.op)
			HYPERVISOR_grant_table_op(GNTTABOP_cache_flush, &cflush, 1);

		offset = 0;
		xen_pfn++;
		left -= len;
	} while (left);
}
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
typedef  int u64 ;
struct resource {int /*<<< orphan*/  end; struct resource* sibling; } ;
typedef  int resource_size_t ;
struct TYPE_2__ {struct resource* child; } ;

/* Variables and functions */
 TYPE_1__ iomem_resource ; 
 int max (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mem_encrypt_active () ; 
 scalar_t__ xen_pv_domain () ; 

bool drm_need_swiotlb(int dma_bits)
{
	struct resource *tmp;
	resource_size_t max_iomem = 0;

	/*
	 * Xen paravirtual hosts require swiotlb regardless of requested dma
	 * transfer size.
	 *
	 * NOTE: Really, what it requires is use of the dma_alloc_coherent
	 *       allocator used in ttm_dma_populate() instead of
	 *       ttm_populate_and_map_pages(), which bounce buffers so much in
	 *       Xen it leads to swiotlb buffer exhaustion.
	 */
	if (xen_pv_domain())
		return true;

	/*
	 * Enforce dma_alloc_coherent when memory encryption is active as well
	 * for the same reasons as for Xen paravirtual hosts.
	 */
	if (mem_encrypt_active())
		return true;

	for (tmp = iomem_resource.child; tmp; tmp = tmp->sibling) {
		max_iomem = max(max_iomem,  tmp->end);
	}

	return max_iomem > ((u64)1 << dma_bits);
}
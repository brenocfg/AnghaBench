#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_5__ {unsigned long num_pages; scalar_t__ direction; void* state; int /*<<< orphan*/ * pages; } ;
typedef  TYPE_1__ drm_via_sg_info_t ;
struct TYPE_6__ {int mem_addr; int num_lines; int mem_stride; } ;
typedef  TYPE_2__ drm_via_dmablit_t ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FOLL_WRITE ; 
 unsigned long VIA_PFN (int) ; 
 int /*<<< orphan*/  array_size (int,unsigned long) ; 
 void* dr_via_pages_locked ; 
 int get_user_pages_fast (unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vzalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
via_lock_all_dma_pages(drm_via_sg_info_t *vsg,  drm_via_dmablit_t *xfer)
{
	int ret;
	unsigned long first_pfn = VIA_PFN(xfer->mem_addr);
	vsg->num_pages = VIA_PFN(xfer->mem_addr + (xfer->num_lines * xfer->mem_stride - 1)) -
		first_pfn + 1;

	vsg->pages = vzalloc(array_size(sizeof(struct page *), vsg->num_pages));
	if (NULL == vsg->pages)
		return -ENOMEM;
	ret = get_user_pages_fast((unsigned long)xfer->mem_addr,
			vsg->num_pages,
			vsg->direction == DMA_FROM_DEVICE ? FOLL_WRITE : 0,
			vsg->pages);
	if (ret != vsg->num_pages) {
		if (ret < 0)
			return ret;
		vsg->state = dr_via_pages_locked;
		return -EINVAL;
	}
	vsg->state = dr_via_pages_locked;
	DRM_DEBUG("DMA pages locked\n");
	return 0;
}
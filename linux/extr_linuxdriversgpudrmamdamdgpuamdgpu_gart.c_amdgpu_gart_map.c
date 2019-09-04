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
typedef  unsigned int uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  ready; } ;
struct amdgpu_device {TYPE_1__ gart; } ;
typedef  unsigned int dma_addr_t ;

/* Variables and functions */
 unsigned int AMDGPU_GPU_PAGES_IN_CPU_PAGE ; 
 unsigned int AMDGPU_GPU_PAGE_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  amdgpu_gmc_set_pte_pde (struct amdgpu_device*,void*,unsigned int,unsigned int,unsigned int) ; 

int amdgpu_gart_map(struct amdgpu_device *adev, uint64_t offset,
		    int pages, dma_addr_t *dma_addr, uint64_t flags,
		    void *dst)
{
	uint64_t page_base;
	unsigned i, j, t;

	if (!adev->gart.ready) {
		WARN(1, "trying to bind memory to uninitialized GART !\n");
		return -EINVAL;
	}

	t = offset / AMDGPU_GPU_PAGE_SIZE;

	for (i = 0; i < pages; i++) {
		page_base = dma_addr[i];
		for (j = 0; j < AMDGPU_GPU_PAGES_IN_CPU_PAGE; j++, t++) {
			amdgpu_gmc_set_pte_pde(adev, dst, t, page_base, flags);
			page_base += AMDGPU_GPU_PAGE_SIZE;
		}
	}
	return 0;
}
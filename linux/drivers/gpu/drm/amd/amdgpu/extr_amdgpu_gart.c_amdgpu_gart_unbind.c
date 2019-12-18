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
typedef  unsigned int u64 ;
struct TYPE_2__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/ ** pages; int /*<<< orphan*/  ready; } ;
struct amdgpu_device {unsigned int dummy_page_addr; int num_vmhubs; TYPE_1__ gart; } ;

/* Variables and functions */
 unsigned int AMDGPU_GPU_PAGES_IN_CPU_PAGE ; 
 unsigned int AMDGPU_GPU_PAGE_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  amdgpu_asic_flush_hdp (struct amdgpu_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_gmc_flush_gpu_tlb (struct amdgpu_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_gmc_set_pte_pde (struct amdgpu_device*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mb () ; 

int amdgpu_gart_unbind(struct amdgpu_device *adev, uint64_t offset,
			int pages)
{
	unsigned t;
	unsigned p;
	int i, j;
	u64 page_base;
	/* Starting from VEGA10, system bit must be 0 to mean invalid. */
	uint64_t flags = 0;

	if (!adev->gart.ready) {
		WARN(1, "trying to unbind memory from uninitialized GART !\n");
		return -EINVAL;
	}

	t = offset / AMDGPU_GPU_PAGE_SIZE;
	p = t / AMDGPU_GPU_PAGES_IN_CPU_PAGE;
	for (i = 0; i < pages; i++, p++) {
#ifdef CONFIG_DRM_AMDGPU_GART_DEBUGFS
		adev->gart.pages[p] = NULL;
#endif
		page_base = adev->dummy_page_addr;
		if (!adev->gart.ptr)
			continue;

		for (j = 0; j < AMDGPU_GPU_PAGES_IN_CPU_PAGE; j++, t++) {
			amdgpu_gmc_set_pte_pde(adev, adev->gart.ptr,
					       t, page_base, flags);
			page_base += AMDGPU_GPU_PAGE_SIZE;
		}
	}
	mb();
	amdgpu_asic_flush_hdp(adev, NULL);
	for (i = 0; i < adev->num_vmhubs; i++)
		amdgpu_gmc_flush_gpu_tlb(adev, 0, i, 0);

	return 0;
}
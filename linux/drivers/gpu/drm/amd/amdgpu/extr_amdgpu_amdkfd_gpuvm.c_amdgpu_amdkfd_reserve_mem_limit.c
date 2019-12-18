#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
typedef  scalar_t__ u32 ;
struct TYPE_7__ {size_t vram_used; } ;
struct TYPE_6__ {size_t real_vram_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  bdev; } ;
struct amdgpu_device {TYPE_3__ kfd; TYPE_2__ gmc; TYPE_1__ mman; } ;
struct amdgpu_bo {int dummy; } ;
struct TYPE_8__ {scalar_t__ system_mem_used; scalar_t__ max_system_mem_limit; scalar_t__ ttm_mem_used; scalar_t__ max_ttm_mem_limit; int /*<<< orphan*/  mem_limit_lock; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_GEM_DOMAIN_CPU ; 
 scalar_t__ AMDGPU_GEM_DOMAIN_GTT ; 
 scalar_t__ AMDGPU_GEM_DOMAIN_VRAM ; 
 int ENOMEM ; 
 int amdgpu_amdkfd_total_mem_size ; 
 TYPE_4__ kfd_mem_limit ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 size_t ttm_bo_dma_acc_size (int /*<<< orphan*/ *,size_t,int) ; 

__attribute__((used)) static int amdgpu_amdkfd_reserve_mem_limit(struct amdgpu_device *adev,
		uint64_t size, u32 domain, bool sg)
{
	size_t acc_size, system_mem_needed, ttm_mem_needed, vram_needed;
	uint64_t reserved_for_pt = amdgpu_amdkfd_total_mem_size >> 9;
	int ret = 0;

	acc_size = ttm_bo_dma_acc_size(&adev->mman.bdev, size,
				       sizeof(struct amdgpu_bo));

	vram_needed = 0;
	if (domain == AMDGPU_GEM_DOMAIN_GTT) {
		/* TTM GTT memory */
		system_mem_needed = acc_size + size;
		ttm_mem_needed = acc_size + size;
	} else if (domain == AMDGPU_GEM_DOMAIN_CPU && !sg) {
		/* Userptr */
		system_mem_needed = acc_size + size;
		ttm_mem_needed = acc_size;
	} else {
		/* VRAM and SG */
		system_mem_needed = acc_size;
		ttm_mem_needed = acc_size;
		if (domain == AMDGPU_GEM_DOMAIN_VRAM)
			vram_needed = size;
	}

	spin_lock(&kfd_mem_limit.mem_limit_lock);

	if ((kfd_mem_limit.system_mem_used + system_mem_needed >
	     kfd_mem_limit.max_system_mem_limit) ||
	    (kfd_mem_limit.ttm_mem_used + ttm_mem_needed >
	     kfd_mem_limit.max_ttm_mem_limit) ||
	    (adev->kfd.vram_used + vram_needed >
	     adev->gmc.real_vram_size - reserved_for_pt)) {
		ret = -ENOMEM;
	} else {
		kfd_mem_limit.system_mem_used += system_mem_needed;
		kfd_mem_limit.ttm_mem_used += ttm_mem_needed;
		adev->kfd.vram_used += vram_needed;
	}

	spin_unlock(&kfd_mem_limit.mem_limit_lock);
	return ret;
}
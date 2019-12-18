#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ttm_mem_type_manager {unsigned long size; } ;
struct TYPE_3__ {struct ttm_mem_type_manager* man; } ;
struct TYPE_4__ {TYPE_1__ bdev; } ;
struct amdgpu_device {TYPE_2__ mman; } ;

/* Variables and functions */
 int AMDGPU_GEM_DOMAIN_GTT ; 
 int AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,unsigned long,unsigned long) ; 
 unsigned long PAGE_SHIFT ; 
 size_t TTM_PL_TT ; 
 size_t TTM_PL_VRAM ; 

__attribute__((used)) static bool amdgpu_bo_validate_size(struct amdgpu_device *adev,
					  unsigned long size, u32 domain)
{
	struct ttm_mem_type_manager *man = NULL;

	/*
	 * If GTT is part of requested domains the check must succeed to
	 * allow fall back to GTT
	 */
	if (domain & AMDGPU_GEM_DOMAIN_GTT) {
		man = &adev->mman.bdev.man[TTM_PL_TT];

		if (size < (man->size << PAGE_SHIFT))
			return true;
		else
			goto fail;
	}

	if (domain & AMDGPU_GEM_DOMAIN_VRAM) {
		man = &adev->mman.bdev.man[TTM_PL_VRAM];

		if (size < (man->size << PAGE_SHIFT))
			return true;
		else
			goto fail;
	}


	/* TODO add more domains checks, such as AMDGPU_GEM_DOMAIN_CPU */
	return true;

fail:
	DRM_DEBUG("BO size %lu > total memory in domain: %llu\n", size,
		  man->size << PAGE_SHIFT);
	return false;
}
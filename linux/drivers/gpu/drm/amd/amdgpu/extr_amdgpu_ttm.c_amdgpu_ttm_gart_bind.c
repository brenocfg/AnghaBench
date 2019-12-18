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
typedef  size_t uint64_t ;
struct ttm_tt {size_t num_pages; int /*<<< orphan*/ * pages; } ;
struct ttm_buffer_object {struct ttm_tt* ttm; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dma_address; } ;
struct amdgpu_ttm_tt {scalar_t__ offset; TYPE_1__ ttm; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_bo {int flags; } ;

/* Variables and functions */
 int AMDGPU_GEM_CREATE_MQD_GFX9 ; 
 int /*<<< orphan*/  AMDGPU_MTYPE_NC ; 
 size_t AMDGPU_PTE_MTYPE_VG10 (int /*<<< orphan*/ ) ; 
 size_t AMDGPU_PTE_MTYPE_VG10_MASK ; 
 int /*<<< orphan*/  DRM_ERROR (char*,size_t,scalar_t__) ; 
 size_t PAGE_SHIFT ; 
 int amdgpu_gart_bind (struct amdgpu_device*,scalar_t__,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 struct amdgpu_bo* ttm_to_amdgpu_bo (struct ttm_buffer_object*) ; 

int amdgpu_ttm_gart_bind(struct amdgpu_device *adev,
				struct ttm_buffer_object *tbo,
				uint64_t flags)
{
	struct amdgpu_bo *abo = ttm_to_amdgpu_bo(tbo);
	struct ttm_tt *ttm = tbo->ttm;
	struct amdgpu_ttm_tt *gtt = (void *)ttm;
	int r;

	if (abo->flags & AMDGPU_GEM_CREATE_MQD_GFX9) {
		uint64_t page_idx = 1;

		r = amdgpu_gart_bind(adev, gtt->offset, page_idx,
				ttm->pages, gtt->ttm.dma_address, flags);
		if (r)
			goto gart_bind_fail;

		/* Patch mtype of the second part BO */
		flags &= ~AMDGPU_PTE_MTYPE_VG10_MASK;
		flags |= AMDGPU_PTE_MTYPE_VG10(AMDGPU_MTYPE_NC);

		r = amdgpu_gart_bind(adev,
				gtt->offset + (page_idx << PAGE_SHIFT),
				ttm->num_pages - page_idx,
				&ttm->pages[page_idx],
				&(gtt->ttm.dma_address[page_idx]), flags);
	} else {
		r = amdgpu_gart_bind(adev, gtt->offset, ttm->num_pages,
				     ttm->pages, gtt->ttm.dma_address, flags);
	}

gart_bind_fail:
	if (r)
		DRM_ERROR("failed to bind %lu pages at 0x%08llX\n",
			  ttm->num_pages, gtt->offset);

	return r;
}
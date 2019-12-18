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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u64 ;
struct dma_fence {int dummy; } ;
struct amdgpu_cs_parser {TYPE_1__* job; int /*<<< orphan*/  adev; int /*<<< orphan*/  filp; } ;
struct TYPE_2__ {int /*<<< orphan*/  sync; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int amdgpu_sync_fence (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dma_fence*,int) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int drm_syncobj_find_fence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_fence**) ; 

__attribute__((used)) static int amdgpu_syncobj_lookup_and_add_to_sync(struct amdgpu_cs_parser *p,
						 uint32_t handle, u64 point,
						 u64 flags)
{
	struct dma_fence *fence;
	int r;

	r = drm_syncobj_find_fence(p->filp, handle, point, flags, &fence);
	if (r) {
		DRM_ERROR("syncobj %u failed to find fence @ %llu (%d)!\n",
			  handle, point, r);
		return r;
	}

	r = amdgpu_sync_fence(p->adev, &p->job->sync, fence, true);
	dma_fence_put(fence);

	return r;
}
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
struct drm_sched_fence {void* owner; } ;
struct dma_fence {int dummy; } ;
struct amdgpu_amdkfd_fence {int dummy; } ;

/* Variables and functions */
 void* AMDGPU_FENCE_OWNER_KFD ; 
 void* AMDGPU_FENCE_OWNER_UNDEFINED ; 
 struct amdgpu_amdkfd_fence* to_amdgpu_amdkfd_fence (struct dma_fence*) ; 
 struct drm_sched_fence* to_drm_sched_fence (struct dma_fence*) ; 

__attribute__((used)) static void *amdgpu_sync_get_owner(struct dma_fence *f)
{
	struct drm_sched_fence *s_fence;
	struct amdgpu_amdkfd_fence *kfd_fence;

	if (!f)
		return AMDGPU_FENCE_OWNER_UNDEFINED;

	s_fence = to_drm_sched_fence(f);
	if (s_fence)
		return s_fence->owner;

	kfd_fence = to_amdgpu_amdkfd_fence(f);
	if (kfd_fence)
		return AMDGPU_FENCE_OWNER_KFD;

	return AMDGPU_FENCE_OWNER_UNDEFINED;
}
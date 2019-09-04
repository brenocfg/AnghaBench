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
struct dma_fence {int dummy; } ;
struct amdgpu_amdkfd_fence {int /*<<< orphan*/  mm; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* schedule_evict_and_restore_process ) (int /*<<< orphan*/ ,struct dma_fence*) ;} ;

/* Variables and functions */
 scalar_t__ dma_fence_is_signaled (struct dma_fence*) ; 
 TYPE_1__* kgd2kfd ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct dma_fence*) ; 
 struct amdgpu_amdkfd_fence* to_amdgpu_amdkfd_fence (struct dma_fence*) ; 

__attribute__((used)) static bool amdkfd_fence_enable_signaling(struct dma_fence *f)
{
	struct amdgpu_amdkfd_fence *fence = to_amdgpu_amdkfd_fence(f);

	if (!fence)
		return false;

	if (dma_fence_is_signaled(f))
		return true;

	if (!kgd2kfd->schedule_evict_and_restore_process(fence->mm, f))
		return true;

	return false;
}
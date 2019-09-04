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
struct dma_fence {int dummy; } ;
struct amdgpu_amdkfd_fence {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kfree_rcu (struct dma_fence*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmdrop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 struct amdgpu_amdkfd_fence* to_amdgpu_amdkfd_fence (struct dma_fence*) ; 

__attribute__((used)) static void amdkfd_fence_release(struct dma_fence *f)
{
	struct amdgpu_amdkfd_fence *fence = to_amdgpu_amdkfd_fence(f);

	/* Unconditionally signal the fence. The process is getting
	 * terminated.
	 */
	if (WARN_ON(!fence))
		return; /* Not an amdgpu_amdkfd_fence */

	mmdrop(fence->mm);
	kfree_rcu(f, rcu);
}
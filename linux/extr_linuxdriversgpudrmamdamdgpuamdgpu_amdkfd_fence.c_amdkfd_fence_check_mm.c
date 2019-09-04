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
struct mm_struct {int dummy; } ;
struct dma_fence {int dummy; } ;
struct amdgpu_amdkfd_fence {struct mm_struct* mm; } ;

/* Variables and functions */
 struct amdgpu_amdkfd_fence* to_amdgpu_amdkfd_fence (struct dma_fence*) ; 

bool amdkfd_fence_check_mm(struct dma_fence *f, struct mm_struct *mm)
{
	struct amdgpu_amdkfd_fence *fence = to_amdgpu_amdkfd_fence(f);

	if (!fence)
		return false;
	else if (fence->mm == mm)
		return true;

	return false;
}
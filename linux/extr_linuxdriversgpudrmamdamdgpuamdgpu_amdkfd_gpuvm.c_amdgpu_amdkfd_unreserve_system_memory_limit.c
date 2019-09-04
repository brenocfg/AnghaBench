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
struct TYPE_3__ {scalar_t__ acc_size; } ;
struct amdgpu_bo {int flags; scalar_t__ preferred_domains; TYPE_1__ tbo; } ;
struct TYPE_4__ {scalar_t__ system_mem_used; scalar_t__ userptr_mem_used; int /*<<< orphan*/  mem_limit_lock; } ;

/* Variables and functions */
 int AMDGPU_AMDKFD_USERPTR_BO ; 
 scalar_t__ AMDGPU_GEM_DOMAIN_GTT ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 scalar_t__ amdgpu_bo_size (struct amdgpu_bo*) ; 
 TYPE_2__ kfd_mem_limit ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void amdgpu_amdkfd_unreserve_system_memory_limit(struct amdgpu_bo *bo)
{
	spin_lock(&kfd_mem_limit.mem_limit_lock);

	if (bo->flags & AMDGPU_AMDKFD_USERPTR_BO) {
		kfd_mem_limit.system_mem_used -= bo->tbo.acc_size;
		kfd_mem_limit.userptr_mem_used -= amdgpu_bo_size(bo);
	} else if (bo->preferred_domains == AMDGPU_GEM_DOMAIN_GTT) {
		kfd_mem_limit.system_mem_used -=
			(bo->tbo.acc_size + amdgpu_bo_size(bo));
	}
	WARN_ONCE(kfd_mem_limit.system_mem_used < 0,
		  "kfd system memory accounting unbalanced");
	WARN_ONCE(kfd_mem_limit.userptr_mem_used < 0,
		  "kfd userptr memory accounting unbalanced");

	spin_unlock(&kfd_mem_limit.mem_limit_lock);
}
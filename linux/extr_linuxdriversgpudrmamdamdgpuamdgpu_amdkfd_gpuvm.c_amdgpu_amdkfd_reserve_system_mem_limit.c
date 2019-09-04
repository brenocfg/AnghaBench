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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;
struct amdgpu_device {TYPE_1__ mman; } ;
struct amdgpu_bo {int dummy; } ;
struct TYPE_4__ {scalar_t__ system_mem_used; scalar_t__ max_system_mem_limit; scalar_t__ userptr_mem_used; scalar_t__ max_userptr_mem_limit; int /*<<< orphan*/  mem_limit_lock; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_GEM_DOMAIN_CPU ; 
 scalar_t__ AMDGPU_GEM_DOMAIN_GTT ; 
 int ENOMEM ; 
 TYPE_2__ kfd_mem_limit ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 size_t ttm_bo_dma_acc_size (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int amdgpu_amdkfd_reserve_system_mem_limit(struct amdgpu_device *adev,
					      uint64_t size, u32 domain)
{
	size_t acc_size;
	int ret = 0;

	acc_size = ttm_bo_dma_acc_size(&adev->mman.bdev, size,
				       sizeof(struct amdgpu_bo));

	spin_lock(&kfd_mem_limit.mem_limit_lock);
	if (domain == AMDGPU_GEM_DOMAIN_GTT) {
		if (kfd_mem_limit.system_mem_used + (acc_size + size) >
			kfd_mem_limit.max_system_mem_limit) {
			ret = -ENOMEM;
			goto err_no_mem;
		}
		kfd_mem_limit.system_mem_used += (acc_size + size);
	} else if (domain == AMDGPU_GEM_DOMAIN_CPU) {
		if ((kfd_mem_limit.system_mem_used + acc_size >
			kfd_mem_limit.max_system_mem_limit) ||
			(kfd_mem_limit.userptr_mem_used + (size + acc_size) >
			kfd_mem_limit.max_userptr_mem_limit)) {
			ret = -ENOMEM;
			goto err_no_mem;
		}
		kfd_mem_limit.system_mem_used += acc_size;
		kfd_mem_limit.userptr_mem_used += size;
	}
err_no_mem:
	spin_unlock(&kfd_mem_limit.mem_limit_lock);
	return ret;
}
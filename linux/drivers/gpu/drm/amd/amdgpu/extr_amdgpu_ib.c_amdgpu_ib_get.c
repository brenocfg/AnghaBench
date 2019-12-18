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
struct amdgpu_vm {int dummy; } ;
struct amdgpu_ib {int /*<<< orphan*/  sa_bo; int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/  ptr; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  ring_tmp_bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_sa_bo_cpu_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_sa_bo_gpu_addr (int /*<<< orphan*/ ) ; 
 int amdgpu_sa_bo_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

int amdgpu_ib_get(struct amdgpu_device *adev, struct amdgpu_vm *vm,
		  unsigned size, struct amdgpu_ib *ib)
{
	int r;

	if (size) {
		r = amdgpu_sa_bo_new(&adev->ring_tmp_bo,
				      &ib->sa_bo, size, 256);
		if (r) {
			dev_err(adev->dev, "failed to get a new IB (%d)\n", r);
			return r;
		}

		ib->ptr = amdgpu_sa_bo_cpu_addr(ib->sa_bo);

		if (!vm)
			ib->gpu_addr = amdgpu_sa_bo_gpu_addr(ib->sa_bo);
	}

	return 0;
}
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
struct amdgpu_device {int ib_pool_ready; int /*<<< orphan*/  ring_tmp_bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_sa_bo_manager_fini (struct amdgpu_device*,int /*<<< orphan*/ *) ; 

void amdgpu_ib_pool_fini(struct amdgpu_device *adev)
{
	if (adev->ib_pool_ready) {
		amdgpu_sa_bo_manager_fini(adev, &adev->ring_tmp_bo);
		adev->ib_pool_ready = false;
	}
}
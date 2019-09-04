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
struct amdgpu_kiq {int /*<<< orphan*/  eop_gpu_addr; int /*<<< orphan*/  eop_obj; } ;
struct TYPE_2__ {struct amdgpu_kiq kiq; } ;
struct amdgpu_device {TYPE_1__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void amdgpu_gfx_kiq_fini(struct amdgpu_device *adev)
{
	struct amdgpu_kiq *kiq = &adev->gfx.kiq;

	amdgpu_bo_free_kernel(&kiq->eop_obj, &kiq->eop_gpu_addr, NULL);
}
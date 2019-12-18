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
struct TYPE_3__ {int /*<<< orphan*/  rlc_autoload_ptr; int /*<<< orphan*/  rlc_autoload_gpu_addr; int /*<<< orphan*/  rlc_autoload_bo; int /*<<< orphan*/  rlc_toc_buf; int /*<<< orphan*/  rlc_toc_gpu_addr; int /*<<< orphan*/  rlc_toc_bo; } ;
struct TYPE_4__ {TYPE_1__ rlc; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static void gfx_v10_0_rlc_backdoor_autoload_buffer_fini(struct amdgpu_device *adev)
{
	amdgpu_bo_free_kernel(&adev->gfx.rlc.rlc_toc_bo,
			      &adev->gfx.rlc.rlc_toc_gpu_addr,
			      (void **)&adev->gfx.rlc.rlc_toc_buf);
	amdgpu_bo_free_kernel(&adev->gfx.rlc.rlc_autoload_bo,
			      &adev->gfx.rlc.rlc_autoload_gpu_addr,
			      (void **)&adev->gfx.rlc.rlc_autoload_ptr);
}
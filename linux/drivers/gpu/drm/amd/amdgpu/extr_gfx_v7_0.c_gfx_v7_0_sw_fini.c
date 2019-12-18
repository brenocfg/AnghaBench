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
struct TYPE_3__ {int /*<<< orphan*/  cp_table_ptr; int /*<<< orphan*/  cp_table_gpu_addr; int /*<<< orphan*/  cp_table_obj; scalar_t__ cp_table_size; int /*<<< orphan*/  cs_ptr; int /*<<< orphan*/  clear_state_gpu_addr; int /*<<< orphan*/  clear_state_obj; } ;
struct TYPE_4__ {int num_gfx_rings; int num_compute_rings; TYPE_1__ rlc; int /*<<< orphan*/ * compute_ring; int /*<<< orphan*/ * gfx_ring; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  amdgpu_gfx_rlc_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ring_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfx_v7_0_cp_compute_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v7_0_free_microcode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v7_0_mec_fini (struct amdgpu_device*) ; 

__attribute__((used)) static int gfx_v7_0_sw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	int i;

	for (i = 0; i < adev->gfx.num_gfx_rings; i++)
		amdgpu_ring_fini(&adev->gfx.gfx_ring[i]);
	for (i = 0; i < adev->gfx.num_compute_rings; i++)
		amdgpu_ring_fini(&adev->gfx.compute_ring[i]);

	gfx_v7_0_cp_compute_fini(adev);
	amdgpu_gfx_rlc_fini(adev);
	gfx_v7_0_mec_fini(adev);
	amdgpu_bo_free_kernel(&adev->gfx.rlc.clear_state_obj,
				&adev->gfx.rlc.clear_state_gpu_addr,
				(void **)&adev->gfx.rlc.cs_ptr);
	if (adev->gfx.rlc.cp_table_size) {
		amdgpu_bo_free_kernel(&adev->gfx.rlc.cp_table_obj,
				&adev->gfx.rlc.cp_table_gpu_addr,
				(void **)&adev->gfx.rlc.cp_table_ptr);
	}
	gfx_v7_0_free_microcode(adev);

	return 0;
}
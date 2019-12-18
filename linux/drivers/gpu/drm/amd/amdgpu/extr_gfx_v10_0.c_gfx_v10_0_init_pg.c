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
struct amdgpu_device {int num_vmhubs; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_gmc_flush_gpu_tlb (struct amdgpu_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfx_v10_0_init_csb (struct amdgpu_device*) ; 

__attribute__((used)) static void gfx_v10_0_init_pg(struct amdgpu_device *adev)
{
	int i;

	gfx_v10_0_init_csb(adev);

	for (i = 0; i < adev->num_vmhubs; i++)
		amdgpu_gmc_flush_gpu_tlb(adev, 0, i, 0);

	/* TODO: init power gating */
	return;
}
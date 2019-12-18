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
typedef  int /*<<< orphan*/  u64 ;
struct amdgpu_gmc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vram_base_offset; } ;
struct amdgpu_device {TYPE_1__ vm_manager; int /*<<< orphan*/  gmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_gmc_gart_location (struct amdgpu_device*,struct amdgpu_gmc*) ; 
 int /*<<< orphan*/  amdgpu_gmc_vram_location (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfxhub_v2_0_get_fb_location (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfxhub_v2_0_get_mc_fb_offset (struct amdgpu_device*) ; 

__attribute__((used)) static void gmc_v10_0_vram_gtt_location(struct amdgpu_device *adev,
					struct amdgpu_gmc *mc)
{
	u64 base = 0;

	if (!amdgpu_sriov_vf(adev))
		base = gfxhub_v2_0_get_fb_location(adev);

	amdgpu_gmc_vram_location(adev, &adev->gmc, base);
	amdgpu_gmc_gart_location(adev, mc);

	/* base offset of vram pages */
	adev->vm_manager.vram_base_offset = gfxhub_v2_0_get_mc_fb_offset(adev);
}
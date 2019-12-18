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
typedef  int u64 ;
struct amdgpu_gmc {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_gmc_gart_location (struct amdgpu_device*,struct amdgpu_gmc*) ; 
 int /*<<< orphan*/  amdgpu_gmc_vram_location (struct amdgpu_device*,struct amdgpu_gmc*,int) ; 
 int /*<<< orphan*/  mmMC_VM_FB_LOCATION ; 

__attribute__((used)) static void gmc_v6_0_vram_gtt_location(struct amdgpu_device *adev,
				       struct amdgpu_gmc *mc)
{
	u64 base = RREG32(mmMC_VM_FB_LOCATION) & 0xFFFF;
	base <<= 24;

	amdgpu_gmc_vram_location(adev, mc, base);
	amdgpu_gmc_gart_location(adev, mc);
}
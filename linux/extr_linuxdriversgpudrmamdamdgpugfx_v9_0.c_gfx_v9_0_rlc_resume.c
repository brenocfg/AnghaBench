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
struct TYPE_2__ {scalar_t__ load_type; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_1__ firmware; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 scalar_t__ CHIP_RAVEN ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_lbpw ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_enable_lbpw (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v9_0_init_csb (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_init_pg (struct amdgpu_device*) ; 
 int gfx_v9_0_rlc_load_microcode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_rlc_reset (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_rlc_start (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_rlc_stop (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmRLC_CGCG_CGLS_CTRL ; 

__attribute__((used)) static int gfx_v9_0_rlc_resume(struct amdgpu_device *adev)
{
	int r;

	if (amdgpu_sriov_vf(adev)) {
		gfx_v9_0_init_csb(adev);
		return 0;
	}

	gfx_v9_0_rlc_stop(adev);

	/* disable CG */
	WREG32_SOC15(GC, 0, mmRLC_CGCG_CGLS_CTRL, 0);

	gfx_v9_0_rlc_reset(adev);

	gfx_v9_0_init_pg(adev);

	if (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP) {
		/* legacy rlc firmware loading */
		r = gfx_v9_0_rlc_load_microcode(adev);
		if (r)
			return r;
	}

	if (adev->asic_type == CHIP_RAVEN) {
		if (amdgpu_lbpw != 0)
			gfx_v9_0_enable_lbpw(adev, true);
		else
			gfx_v9_0_enable_lbpw(adev, false);
	}

	gfx_v9_0_rlc_start(adev);

	return 0;
}
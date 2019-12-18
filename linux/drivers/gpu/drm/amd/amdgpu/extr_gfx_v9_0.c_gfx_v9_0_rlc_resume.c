#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* funcs; } ;
struct TYPE_8__ {TYPE_3__ rlc; } ;
struct TYPE_5__ {scalar_t__ load_type; } ;
struct amdgpu_device {int asic_type; TYPE_4__ gfx; TYPE_1__ firmware; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* start ) (struct amdgpu_device*) ;int /*<<< orphan*/  (* stop ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
#define  CHIP_RAVEN 129 
#define  CHIP_VEGA20 128 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_lbpw ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_enable_lbpw (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v9_0_init_csb (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_init_pg (struct amdgpu_device*) ; 
 int gfx_v9_0_rlc_load_microcode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmRLC_CGCG_CGLS_CTRL ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  stub2 (struct amdgpu_device*) ; 

__attribute__((used)) static int gfx_v9_0_rlc_resume(struct amdgpu_device *adev)
{
	int r;

	if (amdgpu_sriov_vf(adev)) {
		gfx_v9_0_init_csb(adev);
		return 0;
	}

	adev->gfx.rlc.funcs->stop(adev);

	/* disable CG */
	WREG32_SOC15(GC, 0, mmRLC_CGCG_CGLS_CTRL, 0);

	gfx_v9_0_init_pg(adev);

	if (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP) {
		/* legacy rlc firmware loading */
		r = gfx_v9_0_rlc_load_microcode(adev);
		if (r)
			return r;
	}

	switch (adev->asic_type) {
	case CHIP_RAVEN:
		if (amdgpu_lbpw == 0)
			gfx_v9_0_enable_lbpw(adev, false);
		else
			gfx_v9_0_enable_lbpw(adev, true);
		break;
	case CHIP_VEGA20:
		if (amdgpu_lbpw > 0)
			gfx_v9_0_enable_lbpw(adev, true);
		else
			gfx_v9_0_enable_lbpw(adev, false);
		break;
	default:
		break;
	}

	adev->gfx.rlc.funcs->start(adev);

	return 0;
}
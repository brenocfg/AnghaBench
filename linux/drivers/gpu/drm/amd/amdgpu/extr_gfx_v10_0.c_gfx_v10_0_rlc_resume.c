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
struct TYPE_8__ {scalar_t__ load_type; } ;
struct TYPE_6__ {TYPE_1__* funcs; } ;
struct TYPE_7__ {TYPE_2__ rlc; } ;
struct amdgpu_device {TYPE_4__ firmware; TYPE_3__ gfx; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* start ) (struct amdgpu_device*) ;int /*<<< orphan*/  (* stop ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_DIRECT ; 
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 scalar_t__ AMDGPU_FW_LOAD_RLC_BACKDOOR_AUTO ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v10_0_init_pg (struct amdgpu_device*) ; 
 int gfx_v10_0_rlc_backdoor_autoload_enable (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v10_0_rlc_enable_srm (struct amdgpu_device*) ; 
 int gfx_v10_0_rlc_load_microcode (struct amdgpu_device*) ; 
 int gfx_v10_0_wait_for_rlc_autoload_complete (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmRLC_CGCG_CGLS_CTRL ; 
 int /*<<< orphan*/  mmRLC_PG_CNTL ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  stub2 (struct amdgpu_device*) ; 

__attribute__((used)) static int gfx_v10_0_rlc_resume(struct amdgpu_device *adev)
{
	int r;

	if (amdgpu_sriov_vf(adev))
		return 0;

	if (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) {
		r = gfx_v10_0_wait_for_rlc_autoload_complete(adev);
		if (r)
			return r;
		gfx_v10_0_init_pg(adev);

		/* enable RLC SRM */
		gfx_v10_0_rlc_enable_srm(adev);

	} else {
		adev->gfx.rlc.funcs->stop(adev);

		/* disable CG */
		WREG32_SOC15(GC, 0, mmRLC_CGCG_CGLS_CTRL, 0);

		/* disable PG */
		WREG32_SOC15(GC, 0, mmRLC_PG_CNTL, 0);

		if (adev->firmware.load_type == AMDGPU_FW_LOAD_DIRECT) {
			/* legacy rlc firmware loading */
			r = gfx_v10_0_rlc_load_microcode(adev);
			if (r)
				return r;
		} else if (adev->firmware.load_type == AMDGPU_FW_LOAD_RLC_BACKDOOR_AUTO) {
			/* rlc backdoor autoload firmware */
			r = gfx_v10_0_rlc_backdoor_autoload_enable(adev);
			if (r)
				return r;
		}

		gfx_v10_0_init_pg(adev);
		adev->gfx.rlc.funcs->start(adev);

		if (adev->firmware.load_type == AMDGPU_FW_LOAD_RLC_BACKDOOR_AUTO) {
			r = gfx_v10_0_wait_for_rlc_autoload_complete(adev);
			if (r)
				return r;
		}
	}
	return 0;
}
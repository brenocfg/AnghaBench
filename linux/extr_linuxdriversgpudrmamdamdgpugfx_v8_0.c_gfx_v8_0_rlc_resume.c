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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ load_type; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_1__ firmware; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_DIRECT ; 
 scalar_t__ CHIP_POLARIS10 ; 
 scalar_t__ CHIP_POLARIS11 ; 
 scalar_t__ CHIP_POLARIS12 ; 
 scalar_t__ CHIP_VEGAM ; 
 int RLC_CGCG_CGLS_CTRL__CGCG_EN_MASK ; 
 int RLC_CGCG_CGLS_CTRL__CGLS_EN_MASK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfx_v8_0_init_pg (struct amdgpu_device*) ; 
 int gfx_v8_0_rlc_load_microcode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_rlc_reset (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_rlc_start (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_rlc_stop (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmRLC_CGCG_CGLS_CTRL ; 
 int /*<<< orphan*/  mmRLC_CGCG_CGLS_CTRL_3D ; 
 int /*<<< orphan*/  mmRLC_PG_CNTL ; 

__attribute__((used)) static int gfx_v8_0_rlc_resume(struct amdgpu_device *adev)
{
	int r;
	u32 tmp;

	gfx_v8_0_rlc_stop(adev);

	/* disable CG */
	tmp = RREG32(mmRLC_CGCG_CGLS_CTRL);
	tmp &= ~(RLC_CGCG_CGLS_CTRL__CGCG_EN_MASK |
		 RLC_CGCG_CGLS_CTRL__CGLS_EN_MASK);
	WREG32(mmRLC_CGCG_CGLS_CTRL, tmp);
	if (adev->asic_type == CHIP_POLARIS11 ||
	    adev->asic_type == CHIP_POLARIS10 ||
	    adev->asic_type == CHIP_POLARIS12 ||
	    adev->asic_type == CHIP_VEGAM) {
		tmp = RREG32(mmRLC_CGCG_CGLS_CTRL_3D);
		tmp &= ~0x3;
		WREG32(mmRLC_CGCG_CGLS_CTRL_3D, tmp);
	}

	/* disable PG */
	WREG32(mmRLC_PG_CNTL, 0);

	gfx_v8_0_rlc_reset(adev);
	gfx_v8_0_init_pg(adev);


	if (adev->firmware.load_type == AMDGPU_FW_LOAD_DIRECT) {
		/* legacy rlc firmware loading */
		r = gfx_v8_0_rlc_load_microcode(adev);
		if (r)
			return r;
	}

	gfx_v8_0_rlc_start(adev);

	return 0;
}
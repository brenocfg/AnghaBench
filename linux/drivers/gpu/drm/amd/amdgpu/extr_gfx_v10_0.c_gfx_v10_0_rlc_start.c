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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC ; 
 int PP_GFXOFF_MASK ; 
 int /*<<< orphan*/  RLC_CNTL ; 
 int /*<<< orphan*/  RLC_ENABLE_F32 ; 
 int /*<<< orphan*/  WREG32_FIELD15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int amdgpu_pp_feature_mask ; 
 int /*<<< orphan*/  gfx_v10_0_rlc_smu_handshake_cntl (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void gfx_v10_0_rlc_start(struct amdgpu_device *adev)
{
	/* TODO: enable rlc & smu handshake until smu
	 * and gfxoff feature works as expected */
	if (!(amdgpu_pp_feature_mask & PP_GFXOFF_MASK))
		gfx_v10_0_rlc_smu_handshake_cntl(adev, false);

	WREG32_FIELD15(GC, 0, RLC_CNTL, RLC_ENABLE_F32, 1);
	udelay(50);
}
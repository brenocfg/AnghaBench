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
typedef  int uint32_t ;
struct TYPE_3__ {int tcc_disabled_mask; } ;
struct TYPE_4__ {TYPE_1__ config; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGTS_TCC_DISABLE ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  HI_TCC_DISABLE ; 
 int REG_GET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCC_DISABLE ; 
 int /*<<< orphan*/  mmCGTS_TCC_DISABLE ; 
 int /*<<< orphan*/  mmCGTS_USER_TCC_DISABLE ; 

__attribute__((used)) static void gfx_v10_0_get_tcc_info(struct amdgpu_device *adev)
{
	/* TCCs are global (not instanced). */
	uint32_t tcc_disable = RREG32_SOC15(GC, 0, mmCGTS_TCC_DISABLE) |
			       RREG32_SOC15(GC, 0, mmCGTS_USER_TCC_DISABLE);

	adev->gfx.config.tcc_disabled_mask =
		REG_GET_FIELD(tcc_disable, CGTS_TCC_DISABLE, TCC_DISABLE) |
		(REG_GET_FIELD(tcc_disable, CGTS_TCC_DISABLE, HI_TCC_DISABLE) << 16);
}
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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ max_shader_engines; scalar_t__ max_sh_per_se; } ;
struct TYPE_4__ {TYPE_1__ config; } ;
struct amdgpu_device {scalar_t__ usec_timeout; int /*<<< orphan*/  grbm_idx_mutex; TYPE_2__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  GC ; 
 scalar_t__ RLC_SERDES_NONCU_MASTER_BUSY__GC_MASTER_BUSY_MASK ; 
 scalar_t__ RLC_SERDES_NONCU_MASTER_BUSY__SE_MASTER_BUSY_MASK ; 
 scalar_t__ RLC_SERDES_NONCU_MASTER_BUSY__TC0_MASTER_BUSY_MASK ; 
 scalar_t__ RLC_SERDES_NONCU_MASTER_BUSY__TC1_MASTER_BUSY_MASK ; 
 scalar_t__ RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfx_v9_0_select_se_sh (struct amdgpu_device*,int,int,int) ; 
 int /*<<< orphan*/  mmRLC_SERDES_CU_MASTER_BUSY ; 
 int /*<<< orphan*/  mmRLC_SERDES_NONCU_MASTER_BUSY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void gfx_v9_0_wait_for_rlc_serdes(struct amdgpu_device *adev)
{
	u32 i, j, k;
	u32 mask;

	mutex_lock(&adev->grbm_idx_mutex);
	for (i = 0; i < adev->gfx.config.max_shader_engines; i++) {
		for (j = 0; j < adev->gfx.config.max_sh_per_se; j++) {
			gfx_v9_0_select_se_sh(adev, i, j, 0xffffffff);
			for (k = 0; k < adev->usec_timeout; k++) {
				if (RREG32_SOC15(GC, 0, mmRLC_SERDES_CU_MASTER_BUSY) == 0)
					break;
				udelay(1);
			}
			if (k == adev->usec_timeout) {
				gfx_v9_0_select_se_sh(adev, 0xffffffff,
						      0xffffffff, 0xffffffff);
				mutex_unlock(&adev->grbm_idx_mutex);
				DRM_INFO("Timeout wait for RLC serdes %u,%u\n",
					 i, j);
				return;
			}
		}
	}
	gfx_v9_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
	mutex_unlock(&adev->grbm_idx_mutex);

	mask = RLC_SERDES_NONCU_MASTER_BUSY__SE_MASTER_BUSY_MASK |
		RLC_SERDES_NONCU_MASTER_BUSY__GC_MASTER_BUSY_MASK |
		RLC_SERDES_NONCU_MASTER_BUSY__TC0_MASTER_BUSY_MASK |
		RLC_SERDES_NONCU_MASTER_BUSY__TC1_MASTER_BUSY_MASK;
	for (k = 0; k < adev->usec_timeout; k++) {
		if ((RREG32_SOC15(GC, 0, mmRLC_SERDES_NONCU_MASTER_BUSY) & mask) == 0)
			break;
		udelay(1);
	}
}
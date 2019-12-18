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
typedef  int uint32_t ;
struct amdgpu_device {int pg_flags; } ;

/* Variables and functions */
 int AMD_PG_SUPPORT_GFX_DMG ; 
 int AMD_PG_SUPPORT_GFX_PG ; 
 int AMD_PG_SUPPORT_GFX_SMG ; 
 int CP_RB_WPTR_POLL_CNTL__IDLE_POLL_COUNT_MASK ; 
 int CP_RB_WPTR_POLL_CNTL__IDLE_POLL_COUNT__SHIFT ; 
 int /*<<< orphan*/  GC ; 
 int RLC_AUTO_PG_CTRL__GRBM_REG_SAVE_GFX_IDLE_THRESHOLD_MASK ; 
 int RLC_AUTO_PG_CTRL__GRBM_REG_SAVE_GFX_IDLE_THRESHOLD__SHIFT ; 
 int RLC_PG_DELAY_2__SERDES_CMD_DELAY_MASK ; 
 int RLC_PG_DELAY_2__SERDES_CMD_DELAY__SHIFT ; 
 int RLC_PG_DELAY_3__CGCG_ACTIVE_BEFORE_CGPG_MASK ; 
 int RLC_PG_DELAY_3__CGCG_ACTIVE_BEFORE_CGPG__SHIFT ; 
 int RLC_PG_DELAY__CMD_PROPAGATE_DELAY__SHIFT ; 
 int RLC_PG_DELAY__MEM_SLEEP_DELAY__SHIFT ; 
 int RLC_PG_DELAY__POWER_DOWN_DELAY__SHIFT ; 
 int RLC_PG_DELAY__POWER_UP_DELAY__SHIFT ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmCP_RB_WPTR_POLL_CNTL ; 
 int /*<<< orphan*/  mmRLC_AUTO_PG_CTRL ; 
 int /*<<< orphan*/  mmRLC_PG_DELAY ; 
 int /*<<< orphan*/  mmRLC_PG_DELAY_2 ; 
 int /*<<< orphan*/  mmRLC_PG_DELAY_3 ; 
 int /*<<< orphan*/  pwr_10_0_gfxip_control_over_cgpg (struct amdgpu_device*,int) ; 

__attribute__((used)) static void gfx_v9_0_init_gfx_power_gating(struct amdgpu_device *adev)
{
	uint32_t data = 0;

	if (adev->pg_flags & (AMD_PG_SUPPORT_GFX_PG |
			      AMD_PG_SUPPORT_GFX_SMG |
			      AMD_PG_SUPPORT_GFX_DMG)) {
		/* init IDLE_POLL_COUNT = 60 */
		data = RREG32(SOC15_REG_OFFSET(GC, 0, mmCP_RB_WPTR_POLL_CNTL));
		data &= ~CP_RB_WPTR_POLL_CNTL__IDLE_POLL_COUNT_MASK;
		data |= (0x60 << CP_RB_WPTR_POLL_CNTL__IDLE_POLL_COUNT__SHIFT);
		WREG32(SOC15_REG_OFFSET(GC, 0, mmCP_RB_WPTR_POLL_CNTL), data);

		/* init RLC PG Delay */
		data = 0;
		data |= (0x10 << RLC_PG_DELAY__POWER_UP_DELAY__SHIFT);
		data |= (0x10 << RLC_PG_DELAY__POWER_DOWN_DELAY__SHIFT);
		data |= (0x10 << RLC_PG_DELAY__CMD_PROPAGATE_DELAY__SHIFT);
		data |= (0x40 << RLC_PG_DELAY__MEM_SLEEP_DELAY__SHIFT);
		WREG32(SOC15_REG_OFFSET(GC, 0, mmRLC_PG_DELAY), data);

		data = RREG32(SOC15_REG_OFFSET(GC, 0, mmRLC_PG_DELAY_2));
		data &= ~RLC_PG_DELAY_2__SERDES_CMD_DELAY_MASK;
		data |= (0x4 << RLC_PG_DELAY_2__SERDES_CMD_DELAY__SHIFT);
		WREG32(SOC15_REG_OFFSET(GC, 0, mmRLC_PG_DELAY_2), data);

		data = RREG32(SOC15_REG_OFFSET(GC, 0, mmRLC_PG_DELAY_3));
		data &= ~RLC_PG_DELAY_3__CGCG_ACTIVE_BEFORE_CGPG_MASK;
		data |= (0xff << RLC_PG_DELAY_3__CGCG_ACTIVE_BEFORE_CGPG__SHIFT);
		WREG32(SOC15_REG_OFFSET(GC, 0, mmRLC_PG_DELAY_3), data);

		data = RREG32(SOC15_REG_OFFSET(GC, 0, mmRLC_AUTO_PG_CTRL));
		data &= ~RLC_AUTO_PG_CTRL__GRBM_REG_SAVE_GFX_IDLE_THRESHOLD_MASK;

		/* program GRBM_REG_SAVE_GFX_IDLE_THRESHOLD to 0x55f0 */
		data |= (0x55f0 << RLC_AUTO_PG_CTRL__GRBM_REG_SAVE_GFX_IDLE_THRESHOLD__SHIFT);
		WREG32(SOC15_REG_OFFSET(GC, 0, mmRLC_AUTO_PG_CTRL), data);

		pwr_10_0_gfxip_control_over_cgpg(adev, true);
	}
}
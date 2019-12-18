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
typedef  int u32 ;
struct amdgpu_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  GRBM_SOFT_RESET ; 
 int /*<<< orphan*/  GRBM_STATUS2 ; 
 int GRBM_STATUS__BCI_BUSY_MASK ; 
 int GRBM_STATUS__CB_BUSY_MASK ; 
 int GRBM_STATUS__CP_BUSY_MASK ; 
 int GRBM_STATUS__CP_COHERENCY_BUSY_MASK ; 
 int GRBM_STATUS__DB_BUSY_MASK ; 
 int GRBM_STATUS__GDS_BUSY_MASK ; 
 int GRBM_STATUS__GE_BUSY_NO_DMA_MASK ; 
 int GRBM_STATUS__PA_BUSY_MASK ; 
 int GRBM_STATUS__SC_BUSY_MASK ; 
 int GRBM_STATUS__SPI_BUSY_MASK ; 
 int GRBM_STATUS__SX_BUSY_MASK ; 
 int GRBM_STATUS__TA_BUSY_MASK ; 
 scalar_t__ REG_GET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RLC_BUSY ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOFT_RESET_CP ; 
 int /*<<< orphan*/  SOFT_RESET_GFX ; 
 int /*<<< orphan*/  SOFT_RESET_RLC ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gfx_v10_0_cp_compute_enable (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v10_0_cp_gfx_enable (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v10_0_rlc_stop (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmGRBM_SOFT_RESET ; 
 int /*<<< orphan*/  mmGRBM_STATUS ; 
 int /*<<< orphan*/  mmGRBM_STATUS2 ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int gfx_v10_0_soft_reset(void *handle)
{
	u32 grbm_soft_reset = 0;
	u32 tmp;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	/* GRBM_STATUS */
	tmp = RREG32_SOC15(GC, 0, mmGRBM_STATUS);
	if (tmp & (GRBM_STATUS__PA_BUSY_MASK | GRBM_STATUS__SC_BUSY_MASK |
		   GRBM_STATUS__BCI_BUSY_MASK | GRBM_STATUS__SX_BUSY_MASK |
		   GRBM_STATUS__TA_BUSY_MASK | GRBM_STATUS__DB_BUSY_MASK |
		   GRBM_STATUS__CB_BUSY_MASK | GRBM_STATUS__GDS_BUSY_MASK |
		   GRBM_STATUS__SPI_BUSY_MASK | GRBM_STATUS__GE_BUSY_NO_DMA_MASK
		   | GRBM_STATUS__BCI_BUSY_MASK)) {
		grbm_soft_reset = REG_SET_FIELD(grbm_soft_reset,
						GRBM_SOFT_RESET, SOFT_RESET_CP,
						1);
		grbm_soft_reset = REG_SET_FIELD(grbm_soft_reset,
						GRBM_SOFT_RESET, SOFT_RESET_GFX,
						1);
	}

	if (tmp & (GRBM_STATUS__CP_BUSY_MASK | GRBM_STATUS__CP_COHERENCY_BUSY_MASK)) {
		grbm_soft_reset = REG_SET_FIELD(grbm_soft_reset,
						GRBM_SOFT_RESET, SOFT_RESET_CP,
						1);
	}

	/* GRBM_STATUS2 */
	tmp = RREG32_SOC15(GC, 0, mmGRBM_STATUS2);
	if (REG_GET_FIELD(tmp, GRBM_STATUS2, RLC_BUSY))
		grbm_soft_reset = REG_SET_FIELD(grbm_soft_reset,
						GRBM_SOFT_RESET, SOFT_RESET_RLC,
						1);

	if (grbm_soft_reset) {
		/* stop the rlc */
		gfx_v10_0_rlc_stop(adev);

		/* Disable GFX parsing/prefetching */
		gfx_v10_0_cp_gfx_enable(adev, false);

		/* Disable MEC parsing/prefetching */
		gfx_v10_0_cp_compute_enable(adev, false);

		if (grbm_soft_reset) {
			tmp = RREG32_SOC15(GC, 0, mmGRBM_SOFT_RESET);
			tmp |= grbm_soft_reset;
			dev_info(adev->dev, "GRBM_SOFT_RESET=0x%08X\n", tmp);
			WREG32_SOC15(GC, 0, mmGRBM_SOFT_RESET, tmp);
			tmp = RREG32_SOC15(GC, 0, mmGRBM_SOFT_RESET);

			udelay(50);

			tmp &= ~grbm_soft_reset;
			WREG32_SOC15(GC, 0, mmGRBM_SOFT_RESET, tmp);
			tmp = RREG32_SOC15(GC, 0, mmGRBM_SOFT_RESET);
		}

		/* Wait a little for things to settle down */
		udelay(50);
	}
	return 0;
}
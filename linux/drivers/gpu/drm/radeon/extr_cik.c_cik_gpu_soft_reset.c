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
struct radeon_device {int flags; int /*<<< orphan*/  dev; } ;
struct evergreen_mc_save {int dummy; } ;

/* Variables and functions */
 int CP_CE_HALT ; 
 scalar_t__ CP_MEC_CNTL ; 
 scalar_t__ CP_ME_CNTL ; 
 int CP_ME_HALT ; 
 int CP_PFP_HALT ; 
 scalar_t__ GRBM_SOFT_RESET ; 
 int MEC_ME1_HALT ; 
 int MEC_ME2_HALT ; 
 int RADEON_IS_IGP ; 
 int RADEON_RESET_COMPUTE ; 
 int RADEON_RESET_CP ; 
 int RADEON_RESET_DISPLAY ; 
 int RADEON_RESET_DMA ; 
 int RADEON_RESET_DMA1 ; 
 int RADEON_RESET_GFX ; 
 int RADEON_RESET_GRBM ; 
 int RADEON_RESET_IH ; 
 int RADEON_RESET_MC ; 
 int RADEON_RESET_RLC ; 
 int RADEON_RESET_SEM ; 
 int RADEON_RESET_VMC ; 
 int RREG32 (scalar_t__) ; 
 scalar_t__ SDMA0_ME_CNTL ; 
 scalar_t__ SDMA0_REGISTER_OFFSET ; 
 scalar_t__ SDMA1_REGISTER_OFFSET ; 
 int SDMA_HALT ; 
 int SOFT_RESET_CP ; 
 int SOFT_RESET_DC ; 
 int SOFT_RESET_GFX ; 
 int SOFT_RESET_GRBM ; 
 int SOFT_RESET_IH ; 
 int SOFT_RESET_MC ; 
 int SOFT_RESET_RLC ; 
 int SOFT_RESET_SDMA ; 
 int SOFT_RESET_SDMA1 ; 
 int SOFT_RESET_SEM ; 
 int SOFT_RESET_VMC ; 
 scalar_t__ SRBM_SOFT_RESET ; 
 scalar_t__ VM_CONTEXT1_PROTECTION_FAULT_ADDR ; 
 scalar_t__ VM_CONTEXT1_PROTECTION_FAULT_STATUS ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 int /*<<< orphan*/  cik_fini_cg (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_fini_pg (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_print_gpu_status_regs (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_rlc_stop (struct radeon_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evergreen_mc_resume (struct radeon_device*,struct evergreen_mc_save*) ; 
 int /*<<< orphan*/  evergreen_mc_stop (struct radeon_device*,struct evergreen_mc_save*) ; 
 scalar_t__ evergreen_mc_wait_for_idle (struct radeon_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void cik_gpu_soft_reset(struct radeon_device *rdev, u32 reset_mask)
{
	struct evergreen_mc_save save;
	u32 grbm_soft_reset = 0, srbm_soft_reset = 0;
	u32 tmp;

	if (reset_mask == 0)
		return;

	dev_info(rdev->dev, "GPU softreset: 0x%08X\n", reset_mask);

	cik_print_gpu_status_regs(rdev);
	dev_info(rdev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_ADDR   0x%08X\n",
		 RREG32(VM_CONTEXT1_PROTECTION_FAULT_ADDR));
	dev_info(rdev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_STATUS 0x%08X\n",
		 RREG32(VM_CONTEXT1_PROTECTION_FAULT_STATUS));

	/* disable CG/PG */
	cik_fini_pg(rdev);
	cik_fini_cg(rdev);

	/* stop the rlc */
	cik_rlc_stop(rdev);

	/* Disable GFX parsing/prefetching */
	WREG32(CP_ME_CNTL, CP_ME_HALT | CP_PFP_HALT | CP_CE_HALT);

	/* Disable MEC parsing/prefetching */
	WREG32(CP_MEC_CNTL, MEC_ME1_HALT | MEC_ME2_HALT);

	if (reset_mask & RADEON_RESET_DMA) {
		/* sdma0 */
		tmp = RREG32(SDMA0_ME_CNTL + SDMA0_REGISTER_OFFSET);
		tmp |= SDMA_HALT;
		WREG32(SDMA0_ME_CNTL + SDMA0_REGISTER_OFFSET, tmp);
	}
	if (reset_mask & RADEON_RESET_DMA1) {
		/* sdma1 */
		tmp = RREG32(SDMA0_ME_CNTL + SDMA1_REGISTER_OFFSET);
		tmp |= SDMA_HALT;
		WREG32(SDMA0_ME_CNTL + SDMA1_REGISTER_OFFSET, tmp);
	}

	evergreen_mc_stop(rdev, &save);
	if (evergreen_mc_wait_for_idle(rdev)) {
		dev_warn(rdev->dev, "Wait for MC idle timedout !\n");
	}

	if (reset_mask & (RADEON_RESET_GFX | RADEON_RESET_COMPUTE | RADEON_RESET_CP))
		grbm_soft_reset = SOFT_RESET_CP | SOFT_RESET_GFX;

	if (reset_mask & RADEON_RESET_CP) {
		grbm_soft_reset |= SOFT_RESET_CP;

		srbm_soft_reset |= SOFT_RESET_GRBM;
	}

	if (reset_mask & RADEON_RESET_DMA)
		srbm_soft_reset |= SOFT_RESET_SDMA;

	if (reset_mask & RADEON_RESET_DMA1)
		srbm_soft_reset |= SOFT_RESET_SDMA1;

	if (reset_mask & RADEON_RESET_DISPLAY)
		srbm_soft_reset |= SOFT_RESET_DC;

	if (reset_mask & RADEON_RESET_RLC)
		grbm_soft_reset |= SOFT_RESET_RLC;

	if (reset_mask & RADEON_RESET_SEM)
		srbm_soft_reset |= SOFT_RESET_SEM;

	if (reset_mask & RADEON_RESET_IH)
		srbm_soft_reset |= SOFT_RESET_IH;

	if (reset_mask & RADEON_RESET_GRBM)
		srbm_soft_reset |= SOFT_RESET_GRBM;

	if (reset_mask & RADEON_RESET_VMC)
		srbm_soft_reset |= SOFT_RESET_VMC;

	if (!(rdev->flags & RADEON_IS_IGP)) {
		if (reset_mask & RADEON_RESET_MC)
			srbm_soft_reset |= SOFT_RESET_MC;
	}

	if (grbm_soft_reset) {
		tmp = RREG32(GRBM_SOFT_RESET);
		tmp |= grbm_soft_reset;
		dev_info(rdev->dev, "GRBM_SOFT_RESET=0x%08X\n", tmp);
		WREG32(GRBM_SOFT_RESET, tmp);
		tmp = RREG32(GRBM_SOFT_RESET);

		udelay(50);

		tmp &= ~grbm_soft_reset;
		WREG32(GRBM_SOFT_RESET, tmp);
		tmp = RREG32(GRBM_SOFT_RESET);
	}

	if (srbm_soft_reset) {
		tmp = RREG32(SRBM_SOFT_RESET);
		tmp |= srbm_soft_reset;
		dev_info(rdev->dev, "SRBM_SOFT_RESET=0x%08X\n", tmp);
		WREG32(SRBM_SOFT_RESET, tmp);
		tmp = RREG32(SRBM_SOFT_RESET);

		udelay(50);

		tmp &= ~srbm_soft_reset;
		WREG32(SRBM_SOFT_RESET, tmp);
		tmp = RREG32(SRBM_SOFT_RESET);
	}

	/* Wait a little for things to settle down */
	udelay(50);

	evergreen_mc_resume(rdev, &save);
	udelay(50);

	cik_print_gpu_status_regs(rdev);
}
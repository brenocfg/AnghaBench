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
struct rv515_mc_save {int dummy; } ;
struct radeon_device {scalar_t__ family; int flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CHIP_RV770 ; 
 int /*<<< orphan*/  DMA_RB_CNTL ; 
 int DMA_RB_ENABLE ; 
 int RADEON_IS_IGP ; 
 int RADEON_RESET_COMPUTE ; 
 int RADEON_RESET_CP ; 
 int RADEON_RESET_DMA ; 
 int RADEON_RESET_GFX ; 
 int RADEON_RESET_GRBM ; 
 int RADEON_RESET_IH ; 
 int RADEON_RESET_MC ; 
 int RADEON_RESET_RLC ; 
 int RADEON_RESET_SEM ; 
 int RADEON_RESET_VMC ; 
 int /*<<< orphan*/  RLC_CNTL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int RV770_SOFT_RESET_DMA ; 
 int /*<<< orphan*/  R_008020_GRBM_SOFT_RESET ; 
 int /*<<< orphan*/  R_0086D8_CP_ME_CNTL ; 
 int SOFT_RESET_DMA ; 
 int /*<<< orphan*/  SRBM_SOFT_RESET ; 
 int S_000E60_SOFT_RESET_GRBM (int) ; 
 int S_000E60_SOFT_RESET_IH (int) ; 
 int S_000E60_SOFT_RESET_MC (int) ; 
 int S_000E60_SOFT_RESET_RLC (int) ; 
 int S_000E60_SOFT_RESET_SEM (int) ; 
 int S_000E60_SOFT_RESET_VMC (int) ; 
 int S_008020_SOFT_RESET_CB (int) ; 
 int S_008020_SOFT_RESET_CP (int) ; 
 int S_008020_SOFT_RESET_CR (int) ; 
 int S_008020_SOFT_RESET_DB (int) ; 
 int S_008020_SOFT_RESET_PA (int) ; 
 int S_008020_SOFT_RESET_SC (int) ; 
 int S_008020_SOFT_RESET_SH (int) ; 
 int S_008020_SOFT_RESET_SMX (int) ; 
 int S_008020_SOFT_RESET_SPI (int) ; 
 int S_008020_SOFT_RESET_SX (int) ; 
 int S_008020_SOFT_RESET_TA (int) ; 
 int S_008020_SOFT_RESET_TC (int) ; 
 int S_008020_SOFT_RESET_VC (int) ; 
 int S_008020_SOFT_RESET_VGT (int) ; 
 int S_0086D8_CP_ME_HALT (int) ; 
 int S_0086D8_CP_PFP_HALT (int) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ r600_mc_wait_for_idle (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_print_gpu_status_regs (struct radeon_device*) ; 
 int /*<<< orphan*/  rv515_mc_resume (struct radeon_device*,struct rv515_mc_save*) ; 
 int /*<<< orphan*/  rv515_mc_stop (struct radeon_device*,struct rv515_mc_save*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void r600_gpu_soft_reset(struct radeon_device *rdev, u32 reset_mask)
{
	struct rv515_mc_save save;
	u32 grbm_soft_reset = 0, srbm_soft_reset = 0;
	u32 tmp;

	if (reset_mask == 0)
		return;

	dev_info(rdev->dev, "GPU softreset: 0x%08X\n", reset_mask);

	r600_print_gpu_status_regs(rdev);

	/* Disable CP parsing/prefetching */
	if (rdev->family >= CHIP_RV770)
		WREG32(R_0086D8_CP_ME_CNTL, S_0086D8_CP_ME_HALT(1) | S_0086D8_CP_PFP_HALT(1));
	else
		WREG32(R_0086D8_CP_ME_CNTL, S_0086D8_CP_ME_HALT(1));

	/* disable the RLC */
	WREG32(RLC_CNTL, 0);

	if (reset_mask & RADEON_RESET_DMA) {
		/* Disable DMA */
		tmp = RREG32(DMA_RB_CNTL);
		tmp &= ~DMA_RB_ENABLE;
		WREG32(DMA_RB_CNTL, tmp);
	}

	mdelay(50);

	rv515_mc_stop(rdev, &save);
	if (r600_mc_wait_for_idle(rdev)) {
		dev_warn(rdev->dev, "Wait for MC idle timedout !\n");
	}

	if (reset_mask & (RADEON_RESET_GFX | RADEON_RESET_COMPUTE)) {
		if (rdev->family >= CHIP_RV770)
			grbm_soft_reset |= S_008020_SOFT_RESET_DB(1) |
				S_008020_SOFT_RESET_CB(1) |
				S_008020_SOFT_RESET_PA(1) |
				S_008020_SOFT_RESET_SC(1) |
				S_008020_SOFT_RESET_SPI(1) |
				S_008020_SOFT_RESET_SX(1) |
				S_008020_SOFT_RESET_SH(1) |
				S_008020_SOFT_RESET_TC(1) |
				S_008020_SOFT_RESET_TA(1) |
				S_008020_SOFT_RESET_VC(1) |
				S_008020_SOFT_RESET_VGT(1);
		else
			grbm_soft_reset |= S_008020_SOFT_RESET_CR(1) |
				S_008020_SOFT_RESET_DB(1) |
				S_008020_SOFT_RESET_CB(1) |
				S_008020_SOFT_RESET_PA(1) |
				S_008020_SOFT_RESET_SC(1) |
				S_008020_SOFT_RESET_SMX(1) |
				S_008020_SOFT_RESET_SPI(1) |
				S_008020_SOFT_RESET_SX(1) |
				S_008020_SOFT_RESET_SH(1) |
				S_008020_SOFT_RESET_TC(1) |
				S_008020_SOFT_RESET_TA(1) |
				S_008020_SOFT_RESET_VC(1) |
				S_008020_SOFT_RESET_VGT(1);
	}

	if (reset_mask & RADEON_RESET_CP) {
		grbm_soft_reset |= S_008020_SOFT_RESET_CP(1) |
			S_008020_SOFT_RESET_VGT(1);

		srbm_soft_reset |= S_000E60_SOFT_RESET_GRBM(1);
	}

	if (reset_mask & RADEON_RESET_DMA) {
		if (rdev->family >= CHIP_RV770)
			srbm_soft_reset |= RV770_SOFT_RESET_DMA;
		else
			srbm_soft_reset |= SOFT_RESET_DMA;
	}

	if (reset_mask & RADEON_RESET_RLC)
		srbm_soft_reset |= S_000E60_SOFT_RESET_RLC(1);

	if (reset_mask & RADEON_RESET_SEM)
		srbm_soft_reset |= S_000E60_SOFT_RESET_SEM(1);

	if (reset_mask & RADEON_RESET_IH)
		srbm_soft_reset |= S_000E60_SOFT_RESET_IH(1);

	if (reset_mask & RADEON_RESET_GRBM)
		srbm_soft_reset |= S_000E60_SOFT_RESET_GRBM(1);

	if (!(rdev->flags & RADEON_IS_IGP)) {
		if (reset_mask & RADEON_RESET_MC)
			srbm_soft_reset |= S_000E60_SOFT_RESET_MC(1);
	}

	if (reset_mask & RADEON_RESET_VMC)
		srbm_soft_reset |= S_000E60_SOFT_RESET_VMC(1);

	if (grbm_soft_reset) {
		tmp = RREG32(R_008020_GRBM_SOFT_RESET);
		tmp |= grbm_soft_reset;
		dev_info(rdev->dev, "R_008020_GRBM_SOFT_RESET=0x%08X\n", tmp);
		WREG32(R_008020_GRBM_SOFT_RESET, tmp);
		tmp = RREG32(R_008020_GRBM_SOFT_RESET);

		udelay(50);

		tmp &= ~grbm_soft_reset;
		WREG32(R_008020_GRBM_SOFT_RESET, tmp);
		tmp = RREG32(R_008020_GRBM_SOFT_RESET);
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
	mdelay(1);

	rv515_mc_resume(rdev, &save);
	udelay(50);

	r600_print_gpu_status_regs(rdev);
}
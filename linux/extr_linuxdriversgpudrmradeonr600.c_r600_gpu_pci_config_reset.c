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
typedef  scalar_t__ u32 ;
struct rv515_mc_save {int dummy; } ;
struct radeon_device {scalar_t__ family; scalar_t__ usec_timeout; int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIF_SCRATCH0 ; 
 int /*<<< orphan*/  BUS_CNTL ; 
 scalar_t__ CHIP_RV770 ; 
 int /*<<< orphan*/  CONFIG_MEMSIZE ; 
 int /*<<< orphan*/  DMA_RB_CNTL ; 
 scalar_t__ DMA_RB_ENABLE ; 
 int /*<<< orphan*/  RLC_CNTL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_0086D8_CP_ME_CNTL ; 
 scalar_t__ SOFT_RESET_BIF ; 
 int /*<<< orphan*/  SRBM_SOFT_RESET ; 
 scalar_t__ S_0086D8_CP_ME_HALT (int) ; 
 scalar_t__ S_0086D8_CP_PFP_HALT (int) ; 
 scalar_t__ VGA_COHE_SPEC_TIMER_DIS ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pci_clear_master (int /*<<< orphan*/ ) ; 
 scalar_t__ r600_mc_wait_for_idle (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_pci_config_reset (struct radeon_device*) ; 
 int /*<<< orphan*/  rv515_mc_stop (struct radeon_device*,struct rv515_mc_save*) ; 
 int /*<<< orphan*/  rv770_set_clk_bypass_mode (struct radeon_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void r600_gpu_pci_config_reset(struct radeon_device *rdev)
{
	struct rv515_mc_save save;
	u32 tmp, i;

	dev_info(rdev->dev, "GPU pci config reset\n");

	/* disable dpm? */

	/* Disable CP parsing/prefetching */
	if (rdev->family >= CHIP_RV770)
		WREG32(R_0086D8_CP_ME_CNTL, S_0086D8_CP_ME_HALT(1) | S_0086D8_CP_PFP_HALT(1));
	else
		WREG32(R_0086D8_CP_ME_CNTL, S_0086D8_CP_ME_HALT(1));

	/* disable the RLC */
	WREG32(RLC_CNTL, 0);

	/* Disable DMA */
	tmp = RREG32(DMA_RB_CNTL);
	tmp &= ~DMA_RB_ENABLE;
	WREG32(DMA_RB_CNTL, tmp);

	mdelay(50);

	/* set mclk/sclk to bypass */
	if (rdev->family >= CHIP_RV770)
		rv770_set_clk_bypass_mode(rdev);
	/* disable BM */
	pci_clear_master(rdev->pdev);
	/* disable mem access */
	rv515_mc_stop(rdev, &save);
	if (r600_mc_wait_for_idle(rdev)) {
		dev_warn(rdev->dev, "Wait for MC idle timedout !\n");
	}

	/* BIF reset workaround.  Not sure if this is needed on 6xx */
	tmp = RREG32(BUS_CNTL);
	tmp |= VGA_COHE_SPEC_TIMER_DIS;
	WREG32(BUS_CNTL, tmp);

	tmp = RREG32(BIF_SCRATCH0);

	/* reset */
	radeon_pci_config_reset(rdev);
	mdelay(1);

	/* BIF reset workaround.  Not sure if this is needed on 6xx */
	tmp = SOFT_RESET_BIF;
	WREG32(SRBM_SOFT_RESET, tmp);
	mdelay(1);
	WREG32(SRBM_SOFT_RESET, 0);

	/* wait for asic to come out of reset */
	for (i = 0; i < rdev->usec_timeout; i++) {
		if (RREG32(CONFIG_MEMSIZE) != 0xffffffff)
			break;
		udelay(1);
	}
}
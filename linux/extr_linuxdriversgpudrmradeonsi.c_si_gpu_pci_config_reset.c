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
struct radeon_device {scalar_t__ usec_timeout; int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev; } ;
struct evergreen_mc_save {int dummy; } ;

/* Variables and functions */
 scalar_t__ CONFIG_MEMSIZE ; 
 scalar_t__ CP_CE_HALT ; 
 scalar_t__ CP_ME_CNTL ; 
 scalar_t__ CP_ME_HALT ; 
 scalar_t__ CP_PFP_HALT ; 
 scalar_t__ DMA0_REGISTER_OFFSET ; 
 scalar_t__ DMA1_REGISTER_OFFSET ; 
 scalar_t__ DMA_RB_CNTL ; 
 scalar_t__ DMA_RB_ENABLE ; 
 int RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evergreen_mc_stop (struct radeon_device*,struct evergreen_mc_save*) ; 
 scalar_t__ evergreen_mc_wait_for_idle (struct radeon_device*) ; 
 int /*<<< orphan*/  pci_clear_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_pci_config_reset (struct radeon_device*) ; 
 int /*<<< orphan*/  si_fini_cg (struct radeon_device*) ; 
 int /*<<< orphan*/  si_fini_pg (struct radeon_device*) ; 
 int /*<<< orphan*/  si_rlc_stop (struct radeon_device*) ; 
 int /*<<< orphan*/  si_set_clk_bypass_mode (struct radeon_device*) ; 
 int /*<<< orphan*/  si_spll_powerdown (struct radeon_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void si_gpu_pci_config_reset(struct radeon_device *rdev)
{
	struct evergreen_mc_save save;
	u32 tmp, i;

	dev_info(rdev->dev, "GPU pci config reset\n");

	/* disable dpm? */

	/* disable cg/pg */
	si_fini_pg(rdev);
	si_fini_cg(rdev);

	/* Disable CP parsing/prefetching */
	WREG32(CP_ME_CNTL, CP_ME_HALT | CP_PFP_HALT | CP_CE_HALT);
	/* dma0 */
	tmp = RREG32(DMA_RB_CNTL + DMA0_REGISTER_OFFSET);
	tmp &= ~DMA_RB_ENABLE;
	WREG32(DMA_RB_CNTL + DMA0_REGISTER_OFFSET, tmp);
	/* dma1 */
	tmp = RREG32(DMA_RB_CNTL + DMA1_REGISTER_OFFSET);
	tmp &= ~DMA_RB_ENABLE;
	WREG32(DMA_RB_CNTL + DMA1_REGISTER_OFFSET, tmp);
	/* XXX other engines? */

	/* halt the rlc, disable cp internal ints */
	si_rlc_stop(rdev);

	udelay(50);

	/* disable mem access */
	evergreen_mc_stop(rdev, &save);
	if (evergreen_mc_wait_for_idle(rdev)) {
		dev_warn(rdev->dev, "Wait for MC idle timed out !\n");
	}

	/* set mclk/sclk to bypass */
	si_set_clk_bypass_mode(rdev);
	/* powerdown spll */
	si_spll_powerdown(rdev);
	/* disable BM */
	pci_clear_master(rdev->pdev);
	/* reset */
	radeon_pci_config_reset(rdev);
	/* wait for asic to come out of reset */
	for (i = 0; i < rdev->usec_timeout; i++) {
		if (RREG32(CONFIG_MEMSIZE) != 0xffffffff)
			break;
		udelay(1);
	}
}
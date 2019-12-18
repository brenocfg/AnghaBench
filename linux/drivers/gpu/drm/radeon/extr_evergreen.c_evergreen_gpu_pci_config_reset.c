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
struct radeon_device {scalar_t__ usec_timeout; int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; } ;
struct evergreen_mc_save {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_MEMSIZE ; 
 int /*<<< orphan*/  CP_ME_CNTL ; 
 scalar_t__ CP_ME_HALT ; 
 scalar_t__ CP_PFP_HALT ; 
 int /*<<< orphan*/  DMA_RB_CNTL ; 
 scalar_t__ DMA_RB_ENABLE ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evergreen_mc_stop (struct radeon_device*,struct evergreen_mc_save*) ; 
 scalar_t__ evergreen_mc_wait_for_idle (struct radeon_device*) ; 
 int /*<<< orphan*/  pci_clear_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_rlc_stop (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_pci_config_reset (struct radeon_device*) ; 
 int /*<<< orphan*/  rv770_set_clk_bypass_mode (struct radeon_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

void evergreen_gpu_pci_config_reset(struct radeon_device *rdev)
{
	struct evergreen_mc_save save;
	u32 tmp, i;

	dev_info(rdev->dev, "GPU pci config reset\n");

	/* disable dpm? */

	/* Disable CP parsing/prefetching */
	WREG32(CP_ME_CNTL, CP_ME_HALT | CP_PFP_HALT);
	udelay(50);
	/* Disable DMA */
	tmp = RREG32(DMA_RB_CNTL);
	tmp &= ~DMA_RB_ENABLE;
	WREG32(DMA_RB_CNTL, tmp);
	/* XXX other engines? */

	/* halt the rlc */
	r600_rlc_stop(rdev);

	udelay(50);

	/* set mclk/sclk to bypass */
	rv770_set_clk_bypass_mode(rdev);
	/* disable BM */
	pci_clear_master(rdev->pdev);
	/* disable mem access */
	evergreen_mc_stop(rdev, &save);
	if (evergreen_mc_wait_for_idle(rdev)) {
		dev_warn(rdev->dev, "Wait for MC idle timed out !\n");
	}
	/* reset */
	radeon_pci_config_reset(rdev);
	/* wait for asic to come out of reset */
	for (i = 0; i < rdev->usec_timeout; i++) {
		if (RREG32(CONFIG_MEMSIZE) != 0xffffffff)
			break;
		udelay(1);
	}
}
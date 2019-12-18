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
struct radeon_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_BUSY_STAT ; 
 int /*<<< orphan*/  CP_STALLED_STAT1 ; 
 int /*<<< orphan*/  CP_STALLED_STAT2 ; 
 int /*<<< orphan*/  CP_STAT ; 
 int /*<<< orphan*/  DMA_STATUS_REG ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_000E50_SRBM_STATUS ; 
 int /*<<< orphan*/  R_008010_GRBM_STATUS ; 
 int /*<<< orphan*/  R_008014_GRBM_STATUS2 ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r600_print_gpu_status_regs(struct radeon_device *rdev)
{
	dev_info(rdev->dev, "  R_008010_GRBM_STATUS      = 0x%08X\n",
		 RREG32(R_008010_GRBM_STATUS));
	dev_info(rdev->dev, "  R_008014_GRBM_STATUS2     = 0x%08X\n",
		 RREG32(R_008014_GRBM_STATUS2));
	dev_info(rdev->dev, "  R_000E50_SRBM_STATUS      = 0x%08X\n",
		 RREG32(R_000E50_SRBM_STATUS));
	dev_info(rdev->dev, "  R_008674_CP_STALLED_STAT1 = 0x%08X\n",
		 RREG32(CP_STALLED_STAT1));
	dev_info(rdev->dev, "  R_008678_CP_STALLED_STAT2 = 0x%08X\n",
		 RREG32(CP_STALLED_STAT2));
	dev_info(rdev->dev, "  R_00867C_CP_BUSY_STAT     = 0x%08X\n",
		 RREG32(CP_BUSY_STAT));
	dev_info(rdev->dev, "  R_008680_CP_STAT          = 0x%08X\n",
		 RREG32(CP_STAT));
	dev_info(rdev->dev, "  R_00D034_DMA_STATUS_REG   = 0x%08X\n",
		RREG32(DMA_STATUS_REG));
}
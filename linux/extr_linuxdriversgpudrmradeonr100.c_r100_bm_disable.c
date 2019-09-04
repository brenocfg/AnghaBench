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
struct radeon_device {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_BUS_CNTL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_000030_BUS_CNTL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pci_clear_master (int /*<<< orphan*/ ) ; 

void r100_bm_disable(struct radeon_device *rdev)
{
	u32 tmp;

	/* disable bus mastering */
	tmp = RREG32(R_000030_BUS_CNTL);
	WREG32(R_000030_BUS_CNTL, (tmp & 0xFFFFFFFF) | 0x00000044);
	mdelay(1);
	WREG32(R_000030_BUS_CNTL, (tmp & 0xFFFFFFFF) | 0x00000042);
	mdelay(1);
	WREG32(R_000030_BUS_CNTL, (tmp & 0xFFFFFFFF) | 0x00000040);
	tmp = RREG32(RADEON_BUS_CNTL);
	mdelay(1);
	pci_clear_master(rdev->pdev);
	mdelay(1);
}
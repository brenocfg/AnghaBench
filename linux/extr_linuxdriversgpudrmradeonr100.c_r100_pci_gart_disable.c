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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_AIC_CNTL ; 
 int /*<<< orphan*/  RADEON_AIC_HI_ADDR ; 
 int /*<<< orphan*/  RADEON_AIC_LO_ADDR ; 
 int RADEON_DIS_OUT_OF_PCI_GART_ACCESS ; 
 int RADEON_PCIGART_TRANSLATE_EN ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

void r100_pci_gart_disable(struct radeon_device *rdev)
{
	uint32_t tmp;

	/* discard memory request outside of configured range */
	tmp = RREG32(RADEON_AIC_CNTL) | RADEON_DIS_OUT_OF_PCI_GART_ACCESS;
	WREG32(RADEON_AIC_CNTL, tmp & ~RADEON_PCIGART_TRANSLATE_EN);
	WREG32(RADEON_AIC_LO_ADDR, 0);
	WREG32(RADEON_AIC_HI_ADDR, 0);
}
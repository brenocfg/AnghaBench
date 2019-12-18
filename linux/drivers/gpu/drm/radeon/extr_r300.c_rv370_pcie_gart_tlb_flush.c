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
 int /*<<< orphan*/  RADEON_PCIE_TX_GART_CNTL ; 
 int RADEON_PCIE_TX_GART_INVALIDATE_TLB ; 
 int RREG32_PCIE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_PCIE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mb () ; 

void rv370_pcie_gart_tlb_flush(struct radeon_device *rdev)
{
	uint32_t tmp;
	int i;

	/* Workaround HW bug do flush 2 times */
	for (i = 0; i < 2; i++) {
		tmp = RREG32_PCIE(RADEON_PCIE_TX_GART_CNTL);
		WREG32_PCIE(RADEON_PCIE_TX_GART_CNTL, tmp | RADEON_PCIE_TX_GART_INVALIDATE_TLB);
		(void)RREG32_PCIE(RADEON_PCIE_TX_GART_CNTL);
		WREG32_PCIE(RADEON_PCIE_TX_GART_CNTL, tmp);
	}
	mb();
}
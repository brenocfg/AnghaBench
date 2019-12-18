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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int /*<<< orphan*/  pciep_idx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_DATA ; 
 int /*<<< orphan*/  PCIE_INDEX ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void cik_pciep_wreg(struct radeon_device *rdev, u32 reg, u32 v)
{
	unsigned long flags;

	spin_lock_irqsave(&rdev->pciep_idx_lock, flags);
	WREG32(PCIE_INDEX, reg);
	(void)RREG32(PCIE_INDEX);
	WREG32(PCIE_DATA, v);
	(void)RREG32(PCIE_DATA);
	spin_unlock_irqrestore(&rdev->pciep_idx_lock, flags);
}
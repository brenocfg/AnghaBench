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
struct radeon_device {int /*<<< orphan*/  mc_idx_lock; } ;

/* Variables and functions */
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RS480_NB_MC_DATA ; 
 int /*<<< orphan*/  RS480_NB_MC_INDEX ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

uint32_t rs400_mc_rreg(struct radeon_device *rdev, uint32_t reg)
{
	unsigned long flags;
	uint32_t r;

	spin_lock_irqsave(&rdev->mc_idx_lock, flags);
	WREG32(RS480_NB_MC_INDEX, reg & 0xff);
	r = RREG32(RS480_NB_MC_DATA);
	WREG32(RS480_NB_MC_INDEX, 0xff);
	spin_unlock_irqrestore(&rdev->mc_idx_lock, flags);
	return r;
}
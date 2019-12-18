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
typedef  int reg ;

/* Variables and functions */
 int /*<<< orphan*/  MC_IND_DATA ; 
 int /*<<< orphan*/  MC_IND_INDEX ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rv515_mc_wreg(struct radeon_device *rdev, uint32_t reg, uint32_t v)
{
	unsigned long flags;

	spin_lock_irqsave(&rdev->mc_idx_lock, flags);
	WREG32(MC_IND_INDEX, 0xff0000 | ((reg) & 0xffff));
	WREG32(MC_IND_DATA, (v));
	WREG32(MC_IND_INDEX, 0);
	spin_unlock_irqrestore(&rdev->mc_idx_lock, flags);
}
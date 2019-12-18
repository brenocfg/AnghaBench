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
struct radeon_device {int /*<<< orphan*/  cg_idx_lock; } ;
typedef  int /*<<< orphan*/  reg ;

/* Variables and functions */
 int /*<<< orphan*/  EVERGREEN_CG_IND_ADDR ; 
 int /*<<< orphan*/  EVERGREEN_CG_IND_DATA ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void eg_cg_wreg(struct radeon_device *rdev, u32 reg, u32 v)
{
	unsigned long flags;

	spin_lock_irqsave(&rdev->cg_idx_lock, flags);
	WREG32(EVERGREEN_CG_IND_ADDR, ((reg) & 0xffff));
	WREG32(EVERGREEN_CG_IND_DATA, (v));
	spin_unlock_irqrestore(&rdev->cg_idx_lock, flags);
}
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
struct radeon_device {int /*<<< orphan*/  didt_idx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIK_DIDT_IND_DATA ; 
 int /*<<< orphan*/  CIK_DIDT_IND_INDEX ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void cik_didt_wreg(struct radeon_device *rdev, u32 reg, u32 v)
{
	unsigned long flags;

	spin_lock_irqsave(&rdev->didt_idx_lock, flags);
	WREG32(CIK_DIDT_IND_INDEX, (reg));
	WREG32(CIK_DIDT_IND_DATA, (v));
	spin_unlock_irqrestore(&rdev->didt_idx_lock, flags);
}
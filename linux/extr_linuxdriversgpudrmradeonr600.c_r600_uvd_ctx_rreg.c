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
struct radeon_device {int /*<<< orphan*/  uvd_idx_lock; } ;
typedef  int /*<<< orphan*/  reg ;

/* Variables and functions */
 int /*<<< orphan*/  R600_UVD_CTX_DATA ; 
 int /*<<< orphan*/  R600_UVD_CTX_INDEX ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

u32 r600_uvd_ctx_rreg(struct radeon_device *rdev, u32 reg)
{
	unsigned long flags;
	u32 r;

	spin_lock_irqsave(&rdev->uvd_idx_lock, flags);
	WREG32(R600_UVD_CTX_INDEX, ((reg) & 0x1ff));
	r = RREG32(R600_UVD_CTX_DATA);
	spin_unlock_irqrestore(&rdev->uvd_idx_lock, flags);
	return r;
}
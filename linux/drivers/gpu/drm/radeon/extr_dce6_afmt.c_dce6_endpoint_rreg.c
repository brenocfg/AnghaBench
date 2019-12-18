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
typedef  scalar_t__ u32 ;
struct radeon_device {int /*<<< orphan*/  end_idx_lock; } ;

/* Variables and functions */
 scalar_t__ AZ_F0_CODEC_ENDPOINT_DATA ; 
 scalar_t__ AZ_F0_CODEC_ENDPOINT_INDEX ; 
 scalar_t__ RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

u32 dce6_endpoint_rreg(struct radeon_device *rdev,
			      u32 block_offset, u32 reg)
{
	unsigned long flags;
	u32 r;

	spin_lock_irqsave(&rdev->end_idx_lock, flags);
	WREG32(AZ_F0_CODEC_ENDPOINT_INDEX + block_offset, reg);
	r = RREG32(AZ_F0_CODEC_ENDPOINT_DATA + block_offset);
	spin_unlock_irqrestore(&rdev->end_idx_lock, flags);

	return r;
}
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
struct radeon_device {int /*<<< orphan*/  end_idx_lock; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE8 (struct radeon_device*) ; 
 int AZ_ENDPOINT_REG_INDEX (int) ; 
 int AZ_ENDPOINT_REG_WRITE_EN ; 
 int AZ_F0_CODEC_ENDPOINT_DATA ; 
 int AZ_F0_CODEC_ENDPOINT_INDEX ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void dce6_endpoint_wreg(struct radeon_device *rdev,
			       u32 block_offset, u32 reg, u32 v)
{
	unsigned long flags;

	spin_lock_irqsave(&rdev->end_idx_lock, flags);
	if (ASIC_IS_DCE8(rdev))
		WREG32(AZ_F0_CODEC_ENDPOINT_INDEX + block_offset, reg);
	else
		WREG32(AZ_F0_CODEC_ENDPOINT_INDEX + block_offset,
		       AZ_ENDPOINT_REG_WRITE_EN | AZ_ENDPOINT_REG_INDEX(reg));
	WREG32(AZ_F0_CODEC_ENDPOINT_DATA + block_offset, v);
	spin_unlock_irqrestore(&rdev->end_idx_lock, flags);
}
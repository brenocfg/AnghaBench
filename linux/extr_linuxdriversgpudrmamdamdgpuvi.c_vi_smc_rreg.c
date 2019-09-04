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
struct amdgpu_device {int /*<<< orphan*/  smc_idx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  RREG32_NO_KIQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_NO_KIQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmSMC_IND_DATA_11 ; 
 int /*<<< orphan*/  mmSMC_IND_INDEX_11 ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u32 vi_smc_rreg(struct amdgpu_device *adev, u32 reg)
{
	unsigned long flags;
	u32 r;

	spin_lock_irqsave(&adev->smc_idx_lock, flags);
	WREG32_NO_KIQ(mmSMC_IND_INDEX_11, (reg));
	r = RREG32_NO_KIQ(mmSMC_IND_DATA_11);
	spin_unlock_irqrestore(&adev->smc_idx_lock, flags);
	return r;
}
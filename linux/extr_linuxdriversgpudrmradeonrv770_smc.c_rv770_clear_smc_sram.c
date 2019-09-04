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
typedef  scalar_t__ u16 ;
struct radeon_device {int /*<<< orphan*/  smc_idx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMC_SRAM_DATA ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv770_set_smc_sram_address (struct radeon_device*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rv770_clear_smc_sram(struct radeon_device *rdev, u16 limit)
{
	unsigned long flags;
	u16 i;

	spin_lock_irqsave(&rdev->smc_idx_lock, flags);
	for (i = 0;  i < limit; i += 4) {
		rv770_set_smc_sram_address(rdev, i, limit);
		WREG32(SMC_SRAM_DATA, 0);
	}
	spin_unlock_irqrestore(&rdev->smc_idx_lock, flags);
}
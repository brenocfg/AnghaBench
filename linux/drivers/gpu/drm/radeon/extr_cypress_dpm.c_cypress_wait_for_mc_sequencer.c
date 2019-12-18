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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct radeon_device {scalar_t__ family; scalar_t__ usec_timeout; } ;

/* Variables and functions */
 int CG_SEQ_RESP_MASK ; 
 int CG_SEQ_RESP_SHIFT ; 
 scalar_t__ CHIP_CEDAR ; 
 scalar_t__ CHIP_CYPRESS ; 
 scalar_t__ CHIP_HEMLOCK ; 
 int /*<<< orphan*/  MC_CG_CONFIG ; 
 int /*<<< orphan*/  MC_CG_CONFIG_MCD ; 
 int /*<<< orphan*/  MC_CONFIG ; 
 int /*<<< orphan*/  MC_CONFIG_MCD ; 
 int /*<<< orphan*/  MC_RD_ENABLE (scalar_t__) ; 
 int /*<<< orphan*/  MC_RD_ENABLE_MASK ; 
 int /*<<< orphan*/  MC_RD_ENABLE_MCD (scalar_t__) ; 
 int /*<<< orphan*/  MC_RD_ENABLE_MCD_MASK ; 
 int /*<<< orphan*/  MC_SEQ_CG ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void cypress_wait_for_mc_sequencer(struct radeon_device *rdev, u8 value)
{
	u32 i, j;
	u32 channels = 2;

	if ((rdev->family == CHIP_CYPRESS) ||
	    (rdev->family == CHIP_HEMLOCK))
		channels = 4;
	else if (rdev->family == CHIP_CEDAR)
		channels = 1;

	for (i = 0; i < channels; i++) {
		if ((rdev->family == CHIP_CYPRESS) ||
		    (rdev->family == CHIP_HEMLOCK)) {
			WREG32_P(MC_CONFIG_MCD, MC_RD_ENABLE_MCD(i), ~MC_RD_ENABLE_MCD_MASK);
			WREG32_P(MC_CG_CONFIG_MCD, MC_RD_ENABLE_MCD(i), ~MC_RD_ENABLE_MCD_MASK);
		} else {
			WREG32_P(MC_CONFIG, MC_RD_ENABLE(i), ~MC_RD_ENABLE_MASK);
			WREG32_P(MC_CG_CONFIG, MC_RD_ENABLE(i), ~MC_RD_ENABLE_MASK);
		}
		for (j = 0; j < rdev->usec_timeout; j++) {
			if (((RREG32(MC_SEQ_CG) & CG_SEQ_RESP_MASK) >> CG_SEQ_RESP_SHIFT) == value)
				break;
			udelay(1);
		}
	}
}
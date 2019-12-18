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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int RADEON_CRTC2_VBLANK_STAT ; 
 int RADEON_CRTC_VBLANK_STAT ; 
 int RADEON_FP2_DETECT_STAT ; 
 int RADEON_FP_DETECT_STAT ; 
 int /*<<< orphan*/  RADEON_GEN_INT_STATUS ; 
 int RADEON_SW_INT_TEST ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t r100_irq_ack(struct radeon_device *rdev)
{
	uint32_t irqs = RREG32(RADEON_GEN_INT_STATUS);
	uint32_t irq_mask = RADEON_SW_INT_TEST |
		RADEON_CRTC_VBLANK_STAT | RADEON_CRTC2_VBLANK_STAT |
		RADEON_FP_DETECT_STAT | RADEON_FP2_DETECT_STAT;

	if (irqs) {
		WREG32(RADEON_GEN_INT_STATUS, irqs);
	}
	return irqs & irq_mask;
}
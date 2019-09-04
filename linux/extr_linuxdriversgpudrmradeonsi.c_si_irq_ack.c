#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int* disp_int; int* grph_int; } ;
struct TYPE_5__ {TYPE_1__ evergreen; } ;
struct TYPE_6__ {TYPE_2__ stat_regs; } ;
struct radeon_device {int num_crtc; TYPE_3__ irq; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_NODCE (struct radeon_device*) ; 
 int DC_HPD1_INTERRUPT ; 
 int DC_HPD1_RX_INTERRUPT ; 
 int /*<<< orphan*/  DC_HPDx_INT_ACK ; 
 int /*<<< orphan*/  DC_HPDx_INT_CONTROL (int) ; 
 int /*<<< orphan*/  DC_HPDx_RX_INT_ACK ; 
 scalar_t__ GRPH_INT_STATUS ; 
 int /*<<< orphan*/  GRPH_PFLIP_INT_CLEAR ; 
 int GRPH_PFLIP_INT_OCCURRED ; 
 int LB_D1_VBLANK_INTERRUPT ; 
 int LB_D1_VLINE_INTERRUPT ; 
 int RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  VBLANK_ACK ; 
 scalar_t__ VBLANK_STATUS ; 
 int /*<<< orphan*/  VLINE_ACK ; 
 scalar_t__ VLINE_STATUS ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_OR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* crtc_offsets ; 
 scalar_t__* si_disp_int_status ; 

__attribute__((used)) static inline void si_irq_ack(struct radeon_device *rdev)
{
	int i, j;
	u32 *disp_int = rdev->irq.stat_regs.evergreen.disp_int;
	u32 *grph_int = rdev->irq.stat_regs.evergreen.grph_int;

	if (ASIC_IS_NODCE(rdev))
		return;

	for (i = 0; i < 6; i++) {
		disp_int[i] = RREG32(si_disp_int_status[i]);
		if (i < rdev->num_crtc)
			grph_int[i] = RREG32(GRPH_INT_STATUS + crtc_offsets[i]);
	}

	/* We write back each interrupt register in pairs of two */
	for (i = 0; i < rdev->num_crtc; i += 2) {
		for (j = i; j < (i + 2); j++) {
			if (grph_int[j] & GRPH_PFLIP_INT_OCCURRED)
				WREG32(GRPH_INT_STATUS + crtc_offsets[j],
				       GRPH_PFLIP_INT_CLEAR);
		}

		for (j = i; j < (i + 2); j++) {
			if (disp_int[j] & LB_D1_VBLANK_INTERRUPT)
				WREG32(VBLANK_STATUS + crtc_offsets[j],
				       VBLANK_ACK);
			if (disp_int[j] & LB_D1_VLINE_INTERRUPT)
				WREG32(VLINE_STATUS + crtc_offsets[j],
				       VLINE_ACK);
		}
	}

	for (i = 0; i < 6; i++) {
		if (disp_int[i] & DC_HPD1_INTERRUPT)
			WREG32_OR(DC_HPDx_INT_CONTROL(i), DC_HPDx_INT_ACK);
	}

	for (i = 0; i < 6; i++) {
		if (disp_int[i] & DC_HPD1_RX_INTERRUPT)
			WREG32_OR(DC_HPDx_INT_CONTROL(i), DC_HPDx_RX_INT_ACK);
	}
}
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
struct radeon_device {int num_crtc; } ;

/* Variables and functions */
 int CNTX_BUSY_INT_ENABLE ; 
 int CNTX_EMPTY_INT_ENABLE ; 
 scalar_t__ CP_INT_CNTL_RING0 ; 
 scalar_t__ CP_ME1_PIPE0_INT_CNTL ; 
 scalar_t__ CP_ME1_PIPE1_INT_CNTL ; 
 scalar_t__ CP_ME1_PIPE2_INT_CNTL ; 
 scalar_t__ CP_ME1_PIPE3_INT_CNTL ; 
 scalar_t__ CP_ME2_PIPE0_INT_CNTL ; 
 scalar_t__ CP_ME2_PIPE1_INT_CNTL ; 
 scalar_t__ CP_ME2_PIPE2_INT_CNTL ; 
 scalar_t__ CP_ME2_PIPE3_INT_CNTL ; 
 scalar_t__ DAC_AUTODETECT_INT_CONTROL ; 
 scalar_t__ DC_HPD1_INT_CONTROL ; 
 scalar_t__ DC_HPD2_INT_CONTROL ; 
 scalar_t__ DC_HPD3_INT_CONTROL ; 
 scalar_t__ DC_HPD4_INT_CONTROL ; 
 scalar_t__ DC_HPD5_INT_CONTROL ; 
 scalar_t__ DC_HPD6_INT_CONTROL ; 
 int DC_HPDx_INT_POLARITY ; 
 scalar_t__ EVERGREEN_CRTC0_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC1_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC2_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC3_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC4_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC5_REGISTER_OFFSET ; 
 scalar_t__ GRBM_INT_CNTL ; 
 scalar_t__ GRPH_INT_CONTROL ; 
 scalar_t__ LB_INTERRUPT_MASK ; 
 int RREG32 (scalar_t__) ; 
 scalar_t__ SDMA0_CNTL ; 
 scalar_t__ SDMA0_REGISTER_OFFSET ; 
 scalar_t__ SDMA1_REGISTER_OFFSET ; 
 scalar_t__ SRBM_INT_CNTL ; 
 int TRAP_ENABLE ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 

__attribute__((used)) static void cik_disable_interrupt_state(struct radeon_device *rdev)
{
	u32 tmp;

	/* gfx ring */
	tmp = RREG32(CP_INT_CNTL_RING0) &
		(CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE);
	WREG32(CP_INT_CNTL_RING0, tmp);
	/* sdma */
	tmp = RREG32(SDMA0_CNTL + SDMA0_REGISTER_OFFSET) & ~TRAP_ENABLE;
	WREG32(SDMA0_CNTL + SDMA0_REGISTER_OFFSET, tmp);
	tmp = RREG32(SDMA0_CNTL + SDMA1_REGISTER_OFFSET) & ~TRAP_ENABLE;
	WREG32(SDMA0_CNTL + SDMA1_REGISTER_OFFSET, tmp);
	/* compute queues */
	WREG32(CP_ME1_PIPE0_INT_CNTL, 0);
	WREG32(CP_ME1_PIPE1_INT_CNTL, 0);
	WREG32(CP_ME1_PIPE2_INT_CNTL, 0);
	WREG32(CP_ME1_PIPE3_INT_CNTL, 0);
	WREG32(CP_ME2_PIPE0_INT_CNTL, 0);
	WREG32(CP_ME2_PIPE1_INT_CNTL, 0);
	WREG32(CP_ME2_PIPE2_INT_CNTL, 0);
	WREG32(CP_ME2_PIPE3_INT_CNTL, 0);
	/* grbm */
	WREG32(GRBM_INT_CNTL, 0);
	/* SRBM */
	WREG32(SRBM_INT_CNTL, 0);
	/* vline/vblank, etc. */
	WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC0_REGISTER_OFFSET, 0);
	WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC1_REGISTER_OFFSET, 0);
	if (rdev->num_crtc >= 4) {
		WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC2_REGISTER_OFFSET, 0);
		WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC3_REGISTER_OFFSET, 0);
	}
	if (rdev->num_crtc >= 6) {
		WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC4_REGISTER_OFFSET, 0);
		WREG32(LB_INTERRUPT_MASK + EVERGREEN_CRTC5_REGISTER_OFFSET, 0);
	}
	/* pflip */
	if (rdev->num_crtc >= 2) {
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC0_REGISTER_OFFSET, 0);
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC1_REGISTER_OFFSET, 0);
	}
	if (rdev->num_crtc >= 4) {
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC2_REGISTER_OFFSET, 0);
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC3_REGISTER_OFFSET, 0);
	}
	if (rdev->num_crtc >= 6) {
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC4_REGISTER_OFFSET, 0);
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC5_REGISTER_OFFSET, 0);
	}

	/* dac hotplug */
	WREG32(DAC_AUTODETECT_INT_CONTROL, 0);

	/* digital hotplug */
	tmp = RREG32(DC_HPD1_INT_CONTROL) & DC_HPDx_INT_POLARITY;
	WREG32(DC_HPD1_INT_CONTROL, tmp);
	tmp = RREG32(DC_HPD2_INT_CONTROL) & DC_HPDx_INT_POLARITY;
	WREG32(DC_HPD2_INT_CONTROL, tmp);
	tmp = RREG32(DC_HPD3_INT_CONTROL) & DC_HPDx_INT_POLARITY;
	WREG32(DC_HPD3_INT_CONTROL, tmp);
	tmp = RREG32(DC_HPD4_INT_CONTROL) & DC_HPDx_INT_POLARITY;
	WREG32(DC_HPD4_INT_CONTROL, tmp);
	tmp = RREG32(DC_HPD5_INT_CONTROL) & DC_HPDx_INT_POLARITY;
	WREG32(DC_HPD5_INT_CONTROL, tmp);
	tmp = RREG32(DC_HPD6_INT_CONTROL) & DC_HPDx_INT_POLARITY;
	WREG32(DC_HPD6_INT_CONTROL, tmp);

}
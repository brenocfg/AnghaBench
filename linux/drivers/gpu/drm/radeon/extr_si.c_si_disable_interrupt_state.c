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
 int /*<<< orphan*/  ASIC_IS_NODCE (struct radeon_device*) ; 
 int CNTX_BUSY_INT_ENABLE ; 
 int CNTX_EMPTY_INT_ENABLE ; 
 scalar_t__ CP_INT_CNTL_RING0 ; 
 scalar_t__ CP_INT_CNTL_RING1 ; 
 scalar_t__ CP_INT_CNTL_RING2 ; 
 scalar_t__ DAC_AUTODETECT_INT_CONTROL ; 
 int /*<<< orphan*/  DC_HPDx_INT_CONTROL (int) ; 
 int /*<<< orphan*/  DC_HPDx_INT_POLARITY ; 
 scalar_t__ DMA0_REGISTER_OFFSET ; 
 scalar_t__ DMA1_REGISTER_OFFSET ; 
 scalar_t__ DMA_CNTL ; 
 scalar_t__ GRBM_INT_CNTL ; 
 scalar_t__ GRPH_INT_CONTROL ; 
 scalar_t__ INT_MASK ; 
 int RREG32 (scalar_t__) ; 
 scalar_t__ SRBM_INT_CNTL ; 
 int TRAP_ENABLE ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 int /*<<< orphan*/  WREG32_AND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* crtc_offsets ; 

__attribute__((used)) static void si_disable_interrupt_state(struct radeon_device *rdev)
{
	int i;
	u32 tmp;

	tmp = RREG32(CP_INT_CNTL_RING0) &
		(CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE);
	WREG32(CP_INT_CNTL_RING0, tmp);
	WREG32(CP_INT_CNTL_RING1, 0);
	WREG32(CP_INT_CNTL_RING2, 0);
	tmp = RREG32(DMA_CNTL + DMA0_REGISTER_OFFSET) & ~TRAP_ENABLE;
	WREG32(DMA_CNTL + DMA0_REGISTER_OFFSET, tmp);
	tmp = RREG32(DMA_CNTL + DMA1_REGISTER_OFFSET) & ~TRAP_ENABLE;
	WREG32(DMA_CNTL + DMA1_REGISTER_OFFSET, tmp);
	WREG32(GRBM_INT_CNTL, 0);
	WREG32(SRBM_INT_CNTL, 0);
	for (i = 0; i < rdev->num_crtc; i++)
		WREG32(INT_MASK + crtc_offsets[i], 0);
	for (i = 0; i < rdev->num_crtc; i++)
		WREG32(GRPH_INT_CONTROL + crtc_offsets[i], 0);

	if (!ASIC_IS_NODCE(rdev)) {
		WREG32(DAC_AUTODETECT_INT_CONTROL, 0);

		for (i = 0; i < 6; i++)
			WREG32_AND(DC_HPDx_INT_CONTROL(i),
				   DC_HPDx_INT_POLARITY);
	}
}
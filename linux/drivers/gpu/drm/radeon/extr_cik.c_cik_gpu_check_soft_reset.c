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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int BCI_BUSY ; 
 int CB_BUSY ; 
 int CP_BUSY ; 
 int CP_COHERENCY_BUSY ; 
 int DB_BUSY ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int GDS_BUSY ; 
 int GRBM_RQ_PENDING ; 
 scalar_t__ GRBM_STATUS ; 
 scalar_t__ GRBM_STATUS2 ; 
 int IA_BUSY ; 
 int IA_BUSY_NO_DMA ; 
 int IH_BUSY ; 
 int MCB_BUSY ; 
 int MCB_NON_DISPLAY_BUSY ; 
 int MCC_BUSY ; 
 int MCD_BUSY ; 
 int PA_BUSY ; 
 int RADEON_RESET_CP ; 
 int RADEON_RESET_DISPLAY ; 
 int RADEON_RESET_DMA ; 
 int RADEON_RESET_DMA1 ; 
 int RADEON_RESET_GFX ; 
 int RADEON_RESET_GRBM ; 
 int RADEON_RESET_IH ; 
 int RADEON_RESET_MC ; 
 int RADEON_RESET_RLC ; 
 int RADEON_RESET_SEM ; 
 int RADEON_RESET_VMC ; 
 int RLC_BUSY ; 
 int RREG32 (scalar_t__) ; 
 int SC_BUSY ; 
 scalar_t__ SDMA0_REGISTER_OFFSET ; 
 scalar_t__ SDMA0_STATUS_REG ; 
 int SDMA1_BUSY ; 
 scalar_t__ SDMA1_REGISTER_OFFSET ; 
 int SDMA_BUSY ; 
 int SDMA_IDLE ; 
 int SEM_BUSY ; 
 int SPI_BUSY ; 
 scalar_t__ SRBM_STATUS ; 
 scalar_t__ SRBM_STATUS2 ; 
 int SX_BUSY ; 
 int TA_BUSY ; 
 int VGT_BUSY ; 
 int VMC_BUSY ; 
 scalar_t__ evergreen_is_display_hung (struct radeon_device*) ; 

u32 cik_gpu_check_soft_reset(struct radeon_device *rdev)
{
	u32 reset_mask = 0;
	u32 tmp;

	/* GRBM_STATUS */
	tmp = RREG32(GRBM_STATUS);
	if (tmp & (PA_BUSY | SC_BUSY |
		   BCI_BUSY | SX_BUSY |
		   TA_BUSY | VGT_BUSY |
		   DB_BUSY | CB_BUSY |
		   GDS_BUSY | SPI_BUSY |
		   IA_BUSY | IA_BUSY_NO_DMA))
		reset_mask |= RADEON_RESET_GFX;

	if (tmp & (CP_BUSY | CP_COHERENCY_BUSY))
		reset_mask |= RADEON_RESET_CP;

	/* GRBM_STATUS2 */
	tmp = RREG32(GRBM_STATUS2);
	if (tmp & RLC_BUSY)
		reset_mask |= RADEON_RESET_RLC;

	/* SDMA0_STATUS_REG */
	tmp = RREG32(SDMA0_STATUS_REG + SDMA0_REGISTER_OFFSET);
	if (!(tmp & SDMA_IDLE))
		reset_mask |= RADEON_RESET_DMA;

	/* SDMA1_STATUS_REG */
	tmp = RREG32(SDMA0_STATUS_REG + SDMA1_REGISTER_OFFSET);
	if (!(tmp & SDMA_IDLE))
		reset_mask |= RADEON_RESET_DMA1;

	/* SRBM_STATUS2 */
	tmp = RREG32(SRBM_STATUS2);
	if (tmp & SDMA_BUSY)
		reset_mask |= RADEON_RESET_DMA;

	if (tmp & SDMA1_BUSY)
		reset_mask |= RADEON_RESET_DMA1;

	/* SRBM_STATUS */
	tmp = RREG32(SRBM_STATUS);

	if (tmp & IH_BUSY)
		reset_mask |= RADEON_RESET_IH;

	if (tmp & SEM_BUSY)
		reset_mask |= RADEON_RESET_SEM;

	if (tmp & GRBM_RQ_PENDING)
		reset_mask |= RADEON_RESET_GRBM;

	if (tmp & VMC_BUSY)
		reset_mask |= RADEON_RESET_VMC;

	if (tmp & (MCB_BUSY | MCB_NON_DISPLAY_BUSY |
		   MCC_BUSY | MCD_BUSY))
		reset_mask |= RADEON_RESET_MC;

	if (evergreen_is_display_hung(rdev))
		reset_mask |= RADEON_RESET_DISPLAY;

	/* Skip MC reset as it's mostly likely not hung, just busy */
	if (reset_mask & RADEON_RESET_MC) {
		DRM_DEBUG("MC busy: 0x%08X, clearing.\n", reset_mask);
		reset_mask &= ~RADEON_RESET_MC;
	}

	return reset_mask;
}
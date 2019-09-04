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
struct radeon_device {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ CHIP_RV770 ; 
 int DMA_IDLE ; 
 int /*<<< orphan*/  DMA_STATUS_REG ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 scalar_t__ G_000E50_GRBM_RQ_PENDING (int) ; 
 scalar_t__ G_000E50_IH_BUSY (int) ; 
 int G_000E50_MCB_BUSY (int) ; 
 int G_000E50_MCDW_BUSY (int) ; 
 int G_000E50_MCDX_BUSY (int) ; 
 int G_000E50_MCDY_BUSY (int) ; 
 int G_000E50_MCDZ_BUSY (int) ; 
 int G_000E50_RLC_BUSY (int) ; 
 int G_000E50_RLC_RQ_PENDING (int) ; 
 scalar_t__ G_000E50_SEM_BUSY (int) ; 
 scalar_t__ G_000E50_VMC_BUSY (int) ; 
 int G_008010_CB03_BUSY (int) ; 
 int G_008010_CF_RQ_PENDING (int) ; 
 int G_008010_CP_BUSY (int) ; 
 int G_008010_CP_COHERENCY_BUSY (int) ; 
 int G_008010_DB03_BUSY (int) ; 
 scalar_t__ G_008010_GRBM_EE_BUSY (int) ; 
 int G_008010_PA_BUSY (int) ; 
 int G_008010_PF_RQ_PENDING (int) ; 
 int G_008010_SC_BUSY (int) ; 
 int G_008010_SH_BUSY (int) ; 
 int G_008010_SPI03_BUSY (int) ; 
 int G_008010_SX_BUSY (int) ; 
 int G_008010_TA03_BUSY (int) ; 
 int G_008010_TA_BUSY (int) ; 
 int G_008010_VGT_BUSY (int) ; 
 int G_008010_VGT_BUSY_NO_DMA (int) ; 
 int RADEON_RESET_CP ; 
 int RADEON_RESET_DISPLAY ; 
 int RADEON_RESET_DMA ; 
 int RADEON_RESET_GFX ; 
 int RADEON_RESET_GRBM ; 
 int RADEON_RESET_IH ; 
 int RADEON_RESET_MC ; 
 int RADEON_RESET_RLC ; 
 int RADEON_RESET_SEM ; 
 int RADEON_RESET_VMC ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_000E50_SRBM_STATUS ; 
 int /*<<< orphan*/  R_008010_GRBM_STATUS ; 
 scalar_t__ r600_is_display_hung (struct radeon_device*) ; 

u32 r600_gpu_check_soft_reset(struct radeon_device *rdev)
{
	u32 reset_mask = 0;
	u32 tmp;

	/* GRBM_STATUS */
	tmp = RREG32(R_008010_GRBM_STATUS);
	if (rdev->family >= CHIP_RV770) {
		if (G_008010_PA_BUSY(tmp) | G_008010_SC_BUSY(tmp) |
		    G_008010_SH_BUSY(tmp) | G_008010_SX_BUSY(tmp) |
		    G_008010_TA_BUSY(tmp) | G_008010_VGT_BUSY(tmp) |
		    G_008010_DB03_BUSY(tmp) | G_008010_CB03_BUSY(tmp) |
		    G_008010_SPI03_BUSY(tmp) | G_008010_VGT_BUSY_NO_DMA(tmp))
			reset_mask |= RADEON_RESET_GFX;
	} else {
		if (G_008010_PA_BUSY(tmp) | G_008010_SC_BUSY(tmp) |
		    G_008010_SH_BUSY(tmp) | G_008010_SX_BUSY(tmp) |
		    G_008010_TA03_BUSY(tmp) | G_008010_VGT_BUSY(tmp) |
		    G_008010_DB03_BUSY(tmp) | G_008010_CB03_BUSY(tmp) |
		    G_008010_SPI03_BUSY(tmp) | G_008010_VGT_BUSY_NO_DMA(tmp))
			reset_mask |= RADEON_RESET_GFX;
	}

	if (G_008010_CF_RQ_PENDING(tmp) | G_008010_PF_RQ_PENDING(tmp) |
	    G_008010_CP_BUSY(tmp) | G_008010_CP_COHERENCY_BUSY(tmp))
		reset_mask |= RADEON_RESET_CP;

	if (G_008010_GRBM_EE_BUSY(tmp))
		reset_mask |= RADEON_RESET_GRBM | RADEON_RESET_GFX | RADEON_RESET_CP;

	/* DMA_STATUS_REG */
	tmp = RREG32(DMA_STATUS_REG);
	if (!(tmp & DMA_IDLE))
		reset_mask |= RADEON_RESET_DMA;

	/* SRBM_STATUS */
	tmp = RREG32(R_000E50_SRBM_STATUS);
	if (G_000E50_RLC_RQ_PENDING(tmp) | G_000E50_RLC_BUSY(tmp))
		reset_mask |= RADEON_RESET_RLC;

	if (G_000E50_IH_BUSY(tmp))
		reset_mask |= RADEON_RESET_IH;

	if (G_000E50_SEM_BUSY(tmp))
		reset_mask |= RADEON_RESET_SEM;

	if (G_000E50_GRBM_RQ_PENDING(tmp))
		reset_mask |= RADEON_RESET_GRBM;

	if (G_000E50_VMC_BUSY(tmp))
		reset_mask |= RADEON_RESET_VMC;

	if (G_000E50_MCB_BUSY(tmp) | G_000E50_MCDZ_BUSY(tmp) |
	    G_000E50_MCDY_BUSY(tmp) | G_000E50_MCDX_BUSY(tmp) |
	    G_000E50_MCDW_BUSY(tmp))
		reset_mask |= RADEON_RESET_MC;

	if (r600_is_display_hung(rdev))
		reset_mask |= RADEON_RESET_DISPLAY;

	/* Skip MC reset as it's mostly likely not hung, just busy */
	if (reset_mask & RADEON_RESET_MC) {
		DRM_DEBUG("MC busy: 0x%08X, clearing.\n", reset_mask);
		reset_mask &= ~RADEON_RESET_MC;
	}

	return reset_mask;
}
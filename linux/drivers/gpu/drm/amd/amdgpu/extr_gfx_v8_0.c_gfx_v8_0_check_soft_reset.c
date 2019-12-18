#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int grbm_soft_reset; int srbm_soft_reset; } ;
struct amdgpu_device {TYPE_1__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPC_BUSY ; 
 int /*<<< orphan*/  CPF_BUSY ; 
 int /*<<< orphan*/  CPG_BUSY ; 
 int /*<<< orphan*/  GRBM_RQ_PENDING ; 
 int /*<<< orphan*/  GRBM_SOFT_RESET ; 
 int /*<<< orphan*/  GRBM_STATUS2 ; 
 int GRBM_STATUS__BCI_BUSY_MASK ; 
 int GRBM_STATUS__CB_BUSY_MASK ; 
 int GRBM_STATUS__CP_BUSY_MASK ; 
 int GRBM_STATUS__CP_COHERENCY_BUSY_MASK ; 
 int GRBM_STATUS__DB_BUSY_MASK ; 
 int GRBM_STATUS__GDS_BUSY_MASK ; 
 int GRBM_STATUS__IA_BUSY_MASK ; 
 int GRBM_STATUS__IA_BUSY_NO_DMA_MASK ; 
 int GRBM_STATUS__PA_BUSY_MASK ; 
 int GRBM_STATUS__SC_BUSY_MASK ; 
 int GRBM_STATUS__SPI_BUSY_MASK ; 
 int GRBM_STATUS__SX_BUSY_MASK ; 
 int GRBM_STATUS__TA_BUSY_MASK ; 
 int GRBM_STATUS__VGT_BUSY_MASK ; 
 scalar_t__ REG_GET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RLC_BUSY ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEM_BUSY ; 
 int /*<<< orphan*/  SOFT_RESET_CP ; 
 int /*<<< orphan*/  SOFT_RESET_CPC ; 
 int /*<<< orphan*/  SOFT_RESET_CPF ; 
 int /*<<< orphan*/  SOFT_RESET_CPG ; 
 int /*<<< orphan*/  SOFT_RESET_GFX ; 
 int /*<<< orphan*/  SOFT_RESET_GRBM ; 
 int /*<<< orphan*/  SOFT_RESET_RLC ; 
 int /*<<< orphan*/  SOFT_RESET_SEM ; 
 int /*<<< orphan*/  SRBM_SOFT_RESET ; 
 int /*<<< orphan*/  SRBM_STATUS ; 
 int /*<<< orphan*/  mmGRBM_STATUS ; 
 int /*<<< orphan*/  mmGRBM_STATUS2 ; 
 int /*<<< orphan*/  mmSRBM_STATUS ; 

__attribute__((used)) static bool gfx_v8_0_check_soft_reset(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	u32 grbm_soft_reset = 0, srbm_soft_reset = 0;
	u32 tmp;

	/* GRBM_STATUS */
	tmp = RREG32(mmGRBM_STATUS);
	if (tmp & (GRBM_STATUS__PA_BUSY_MASK | GRBM_STATUS__SC_BUSY_MASK |
		   GRBM_STATUS__BCI_BUSY_MASK | GRBM_STATUS__SX_BUSY_MASK |
		   GRBM_STATUS__TA_BUSY_MASK | GRBM_STATUS__VGT_BUSY_MASK |
		   GRBM_STATUS__DB_BUSY_MASK | GRBM_STATUS__CB_BUSY_MASK |
		   GRBM_STATUS__GDS_BUSY_MASK | GRBM_STATUS__SPI_BUSY_MASK |
		   GRBM_STATUS__IA_BUSY_MASK | GRBM_STATUS__IA_BUSY_NO_DMA_MASK |
		   GRBM_STATUS__CP_BUSY_MASK | GRBM_STATUS__CP_COHERENCY_BUSY_MASK)) {
		grbm_soft_reset = REG_SET_FIELD(grbm_soft_reset,
						GRBM_SOFT_RESET, SOFT_RESET_CP, 1);
		grbm_soft_reset = REG_SET_FIELD(grbm_soft_reset,
						GRBM_SOFT_RESET, SOFT_RESET_GFX, 1);
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset,
						SRBM_SOFT_RESET, SOFT_RESET_GRBM, 1);
	}

	/* GRBM_STATUS2 */
	tmp = RREG32(mmGRBM_STATUS2);
	if (REG_GET_FIELD(tmp, GRBM_STATUS2, RLC_BUSY))
		grbm_soft_reset = REG_SET_FIELD(grbm_soft_reset,
						GRBM_SOFT_RESET, SOFT_RESET_RLC, 1);

	if (REG_GET_FIELD(tmp, GRBM_STATUS2, CPF_BUSY) ||
	    REG_GET_FIELD(tmp, GRBM_STATUS2, CPC_BUSY) ||
	    REG_GET_FIELD(tmp, GRBM_STATUS2, CPG_BUSY)) {
		grbm_soft_reset = REG_SET_FIELD(grbm_soft_reset, GRBM_SOFT_RESET,
						SOFT_RESET_CPF, 1);
		grbm_soft_reset = REG_SET_FIELD(grbm_soft_reset, GRBM_SOFT_RESET,
						SOFT_RESET_CPC, 1);
		grbm_soft_reset = REG_SET_FIELD(grbm_soft_reset, GRBM_SOFT_RESET,
						SOFT_RESET_CPG, 1);
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset, SRBM_SOFT_RESET,
						SOFT_RESET_GRBM, 1);
	}

	/* SRBM_STATUS */
	tmp = RREG32(mmSRBM_STATUS);
	if (REG_GET_FIELD(tmp, SRBM_STATUS, GRBM_RQ_PENDING))
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset,
						SRBM_SOFT_RESET, SOFT_RESET_GRBM, 1);
	if (REG_GET_FIELD(tmp, SRBM_STATUS, SEM_BUSY))
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset,
						SRBM_SOFT_RESET, SOFT_RESET_SEM, 1);

	if (grbm_soft_reset || srbm_soft_reset) {
		adev->gfx.grbm_soft_reset = grbm_soft_reset;
		adev->gfx.srbm_soft_reset = srbm_soft_reset;
		return true;
	} else {
		adev->gfx.grbm_soft_reset = 0;
		adev->gfx.srbm_soft_reset = 0;
		return false;
	}
}
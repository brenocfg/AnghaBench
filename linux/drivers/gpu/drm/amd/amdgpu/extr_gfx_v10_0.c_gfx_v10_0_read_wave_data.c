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
typedef  scalar_t__ uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ixSQ_WAVE_EXEC_HI ; 
 int /*<<< orphan*/  ixSQ_WAVE_EXEC_LO ; 
 int /*<<< orphan*/  ixSQ_WAVE_GPR_ALLOC ; 
 int /*<<< orphan*/  ixSQ_WAVE_HW_ID1 ; 
 int /*<<< orphan*/  ixSQ_WAVE_HW_ID2 ; 
 int /*<<< orphan*/  ixSQ_WAVE_IB_DBG1 ; 
 int /*<<< orphan*/  ixSQ_WAVE_IB_STS ; 
 int /*<<< orphan*/  ixSQ_WAVE_IB_STS2 ; 
 int /*<<< orphan*/  ixSQ_WAVE_INST_DW0 ; 
 int /*<<< orphan*/  ixSQ_WAVE_LDS_ALLOC ; 
 int /*<<< orphan*/  ixSQ_WAVE_M0 ; 
 int /*<<< orphan*/  ixSQ_WAVE_PC_HI ; 
 int /*<<< orphan*/  ixSQ_WAVE_PC_LO ; 
 int /*<<< orphan*/  ixSQ_WAVE_STATUS ; 
 int /*<<< orphan*/  ixSQ_WAVE_TRAPSTS ; 
 scalar_t__ wave_read_ind (struct amdgpu_device*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfx_v10_0_read_wave_data(struct amdgpu_device *adev, uint32_t simd, uint32_t wave, uint32_t *dst, int *no_fields)
{
	/* in gfx10 the SIMD_ID is specified as part of the INSTANCE
	 * field when performing a select_se_sh so it should be
	 * zero here */
	WARN_ON(simd != 0);

	/* type 2 wave data */
	dst[(*no_fields)++] = 2;
	dst[(*no_fields)++] = wave_read_ind(adev, wave, ixSQ_WAVE_STATUS);
	dst[(*no_fields)++] = wave_read_ind(adev, wave, ixSQ_WAVE_PC_LO);
	dst[(*no_fields)++] = wave_read_ind(adev, wave, ixSQ_WAVE_PC_HI);
	dst[(*no_fields)++] = wave_read_ind(adev, wave, ixSQ_WAVE_EXEC_LO);
	dst[(*no_fields)++] = wave_read_ind(adev, wave, ixSQ_WAVE_EXEC_HI);
	dst[(*no_fields)++] = wave_read_ind(adev, wave, ixSQ_WAVE_HW_ID1);
	dst[(*no_fields)++] = wave_read_ind(adev, wave, ixSQ_WAVE_HW_ID2);
	dst[(*no_fields)++] = wave_read_ind(adev, wave, ixSQ_WAVE_INST_DW0);
	dst[(*no_fields)++] = wave_read_ind(adev, wave, ixSQ_WAVE_GPR_ALLOC);
	dst[(*no_fields)++] = wave_read_ind(adev, wave, ixSQ_WAVE_LDS_ALLOC);
	dst[(*no_fields)++] = wave_read_ind(adev, wave, ixSQ_WAVE_TRAPSTS);
	dst[(*no_fields)++] = wave_read_ind(adev, wave, ixSQ_WAVE_IB_STS);
	dst[(*no_fields)++] = wave_read_ind(adev, wave, ixSQ_WAVE_IB_STS2);
	dst[(*no_fields)++] = wave_read_ind(adev, wave, ixSQ_WAVE_IB_DBG1);
	dst[(*no_fields)++] = wave_read_ind(adev, wave, ixSQ_WAVE_M0);
}
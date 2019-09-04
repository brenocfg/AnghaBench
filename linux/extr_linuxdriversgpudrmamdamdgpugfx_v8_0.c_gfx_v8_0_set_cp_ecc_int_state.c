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
struct amdgpu_irq_src {int dummy; } ;
struct amdgpu_device {int dummy; } ;
typedef  enum amdgpu_interrupt_state { ____Placeholder_amdgpu_interrupt_state } amdgpu_interrupt_state ;

/* Variables and functions */
#define  AMDGPU_IRQ_STATE_DISABLE 129 
#define  AMDGPU_IRQ_STATE_ENABLE 128 
 int /*<<< orphan*/  CPC_INT_CNTL ; 
 int /*<<< orphan*/  CP_ECC_ERROR_INT_ENABLE ; 
 int /*<<< orphan*/  CP_INT_CNTL ; 
 int /*<<< orphan*/  CP_INT_CNTL_RING0 ; 
 int /*<<< orphan*/  CP_INT_CNTL_RING1 ; 
 int /*<<< orphan*/  CP_INT_CNTL_RING2 ; 
 int /*<<< orphan*/  CP_ME1_PIPE0_INT_CNTL ; 
 int /*<<< orphan*/  CP_ME1_PIPE1_INT_CNTL ; 
 int /*<<< orphan*/  CP_ME1_PIPE2_INT_CNTL ; 
 int /*<<< orphan*/  CP_ME1_PIPE3_INT_CNTL ; 
 int /*<<< orphan*/  CP_ME2_PIPE0_INT_CNTL ; 
 int /*<<< orphan*/  CP_ME2_PIPE1_INT_CNTL ; 
 int /*<<< orphan*/  CP_ME2_PIPE2_INT_CNTL ; 
 int /*<<< orphan*/  CP_ME2_PIPE3_INT_CNTL ; 
 int EINVAL ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gfx_v8_0_set_cp_ecc_int_state(struct amdgpu_device *adev,
					 struct amdgpu_irq_src *source,
					 unsigned int type,
					 enum amdgpu_interrupt_state state)
{
	int enable_flag;

	switch (state) {
	case AMDGPU_IRQ_STATE_DISABLE:
		enable_flag = 0;
		break;

	case AMDGPU_IRQ_STATE_ENABLE:
		enable_flag = 1;
		break;

	default:
		return -EINVAL;
	}

	WREG32_FIELD(CP_INT_CNTL, CP_ECC_ERROR_INT_ENABLE, enable_flag);
	WREG32_FIELD(CP_INT_CNTL_RING0, CP_ECC_ERROR_INT_ENABLE, enable_flag);
	WREG32_FIELD(CP_INT_CNTL_RING1, CP_ECC_ERROR_INT_ENABLE, enable_flag);
	WREG32_FIELD(CP_INT_CNTL_RING2, CP_ECC_ERROR_INT_ENABLE, enable_flag);
	WREG32_FIELD(CPC_INT_CNTL, CP_ECC_ERROR_INT_ENABLE, enable_flag);
	WREG32_FIELD(CP_ME1_PIPE0_INT_CNTL, CP_ECC_ERROR_INT_ENABLE,
		     enable_flag);
	WREG32_FIELD(CP_ME1_PIPE1_INT_CNTL, CP_ECC_ERROR_INT_ENABLE,
		     enable_flag);
	WREG32_FIELD(CP_ME1_PIPE2_INT_CNTL, CP_ECC_ERROR_INT_ENABLE,
		     enable_flag);
	WREG32_FIELD(CP_ME1_PIPE3_INT_CNTL, CP_ECC_ERROR_INT_ENABLE,
		     enable_flag);
	WREG32_FIELD(CP_ME2_PIPE0_INT_CNTL, CP_ECC_ERROR_INT_ENABLE,
		     enable_flag);
	WREG32_FIELD(CP_ME2_PIPE1_INT_CNTL, CP_ECC_ERROR_INT_ENABLE,
		     enable_flag);
	WREG32_FIELD(CP_ME2_PIPE2_INT_CNTL, CP_ECC_ERROR_INT_ENABLE,
		     enable_flag);
	WREG32_FIELD(CP_ME2_PIPE3_INT_CNTL, CP_ECC_ERROR_INT_ENABLE,
		     enable_flag);

	return 0;
}
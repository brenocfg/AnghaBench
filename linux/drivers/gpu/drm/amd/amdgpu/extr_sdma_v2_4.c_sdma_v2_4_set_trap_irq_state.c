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
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_irq_src {int dummy; } ;
struct amdgpu_device {int dummy; } ;
typedef  enum amdgpu_interrupt_state { ____Placeholder_amdgpu_interrupt_state } amdgpu_interrupt_state ;

/* Variables and functions */
#define  AMDGPU_IRQ_STATE_DISABLE 131 
#define  AMDGPU_IRQ_STATE_ENABLE 130 
#define  AMDGPU_SDMA_IRQ_INSTANCE0 129 
#define  AMDGPU_SDMA_IRQ_INSTANCE1 128 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  SDMA0_CNTL ; 
 scalar_t__ SDMA0_REGISTER_OFFSET ; 
 scalar_t__ SDMA1_REGISTER_OFFSET ; 
 int /*<<< orphan*/  TRAP_ENABLE ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mmSDMA0_CNTL ; 

__attribute__((used)) static int sdma_v2_4_set_trap_irq_state(struct amdgpu_device *adev,
					struct amdgpu_irq_src *src,
					unsigned type,
					enum amdgpu_interrupt_state state)
{
	u32 sdma_cntl;

	switch (type) {
	case AMDGPU_SDMA_IRQ_INSTANCE0:
		switch (state) {
		case AMDGPU_IRQ_STATE_DISABLE:
			sdma_cntl = RREG32(mmSDMA0_CNTL + SDMA0_REGISTER_OFFSET);
			sdma_cntl = REG_SET_FIELD(sdma_cntl, SDMA0_CNTL, TRAP_ENABLE, 0);
			WREG32(mmSDMA0_CNTL + SDMA0_REGISTER_OFFSET, sdma_cntl);
			break;
		case AMDGPU_IRQ_STATE_ENABLE:
			sdma_cntl = RREG32(mmSDMA0_CNTL + SDMA0_REGISTER_OFFSET);
			sdma_cntl = REG_SET_FIELD(sdma_cntl, SDMA0_CNTL, TRAP_ENABLE, 1);
			WREG32(mmSDMA0_CNTL + SDMA0_REGISTER_OFFSET, sdma_cntl);
			break;
		default:
			break;
		}
		break;
	case AMDGPU_SDMA_IRQ_INSTANCE1:
		switch (state) {
		case AMDGPU_IRQ_STATE_DISABLE:
			sdma_cntl = RREG32(mmSDMA0_CNTL + SDMA1_REGISTER_OFFSET);
			sdma_cntl = REG_SET_FIELD(sdma_cntl, SDMA0_CNTL, TRAP_ENABLE, 0);
			WREG32(mmSDMA0_CNTL + SDMA1_REGISTER_OFFSET, sdma_cntl);
			break;
		case AMDGPU_IRQ_STATE_ENABLE:
			sdma_cntl = RREG32(mmSDMA0_CNTL + SDMA1_REGISTER_OFFSET);
			sdma_cntl = REG_SET_FIELD(sdma_cntl, SDMA0_CNTL, TRAP_ENABLE, 1);
			WREG32(mmSDMA0_CNTL + SDMA1_REGISTER_OFFSET, sdma_cntl);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return 0;
}
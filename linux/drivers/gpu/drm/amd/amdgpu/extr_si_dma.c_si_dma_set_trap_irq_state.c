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
 scalar_t__ DMA0_REGISTER_OFFSET ; 
 scalar_t__ DMA1_REGISTER_OFFSET ; 
 scalar_t__ DMA_CNTL ; 
 int /*<<< orphan*/  RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  TRAP_ENABLE ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si_dma_set_trap_irq_state(struct amdgpu_device *adev,
					struct amdgpu_irq_src *src,
					unsigned type,
					enum amdgpu_interrupt_state state)
{
	u32 sdma_cntl;

	switch (type) {
	case AMDGPU_SDMA_IRQ_INSTANCE0:
		switch (state) {
		case AMDGPU_IRQ_STATE_DISABLE:
			sdma_cntl = RREG32(DMA_CNTL + DMA0_REGISTER_OFFSET);
			sdma_cntl &= ~TRAP_ENABLE;
			WREG32(DMA_CNTL + DMA0_REGISTER_OFFSET, sdma_cntl);
			break;
		case AMDGPU_IRQ_STATE_ENABLE:
			sdma_cntl = RREG32(DMA_CNTL + DMA0_REGISTER_OFFSET);
			sdma_cntl |= TRAP_ENABLE;
			WREG32(DMA_CNTL + DMA0_REGISTER_OFFSET, sdma_cntl);
			break;
		default:
			break;
		}
		break;
	case AMDGPU_SDMA_IRQ_INSTANCE1:
		switch (state) {
		case AMDGPU_IRQ_STATE_DISABLE:
			sdma_cntl = RREG32(DMA_CNTL + DMA1_REGISTER_OFFSET);
			sdma_cntl &= ~TRAP_ENABLE;
			WREG32(DMA_CNTL + DMA1_REGISTER_OFFSET, sdma_cntl);
			break;
		case AMDGPU_IRQ_STATE_ENABLE:
			sdma_cntl = RREG32(DMA_CNTL + DMA1_REGISTER_OFFSET);
			sdma_cntl |= TRAP_ENABLE;
			WREG32(DMA_CNTL + DMA1_REGISTER_OFFSET, sdma_cntl);
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
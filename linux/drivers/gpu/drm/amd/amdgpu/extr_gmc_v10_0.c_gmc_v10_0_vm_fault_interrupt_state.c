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
struct amdgpu_vmhub {int vm_context0_cntl; } ;
struct amdgpu_irq_src {int dummy; } ;
struct amdgpu_device {struct amdgpu_vmhub* vmhub; } ;
typedef  enum amdgpu_interrupt_state { ____Placeholder_amdgpu_interrupt_state } amdgpu_interrupt_state ;

/* Variables and functions */
 size_t AMDGPU_GFXHUB_0 ; 
#define  AMDGPU_IRQ_STATE_DISABLE 129 
#define  AMDGPU_IRQ_STATE_ENABLE 128 
 int AMDGPU_MAX_VMHUBS ; 
 size_t AMDGPU_MMHUB_0 ; 
 int GCVM_CONTEXT1_CNTL__DUMMY_PAGE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK ; 
 int GCVM_CONTEXT1_CNTL__EXECUTE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK ; 
 int GCVM_CONTEXT1_CNTL__PDE0_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK ; 
 int GCVM_CONTEXT1_CNTL__RANGE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK ; 
 int GCVM_CONTEXT1_CNTL__READ_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK ; 
 int GCVM_CONTEXT1_CNTL__VALID_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK ; 
 int GCVM_CONTEXT1_CNTL__WRITE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK ; 
 int MMVM_CONTEXT1_CNTL__DUMMY_PAGE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK ; 
 int MMVM_CONTEXT1_CNTL__EXECUTE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK ; 
 int MMVM_CONTEXT1_CNTL__PDE0_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK ; 
 int MMVM_CONTEXT1_CNTL__RANGE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK ; 
 int MMVM_CONTEXT1_CNTL__READ_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK ; 
 int MMVM_CONTEXT1_CNTL__VALID_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK ; 
 int MMVM_CONTEXT1_CNTL__WRITE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK ; 
 int RREG32 (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 

__attribute__((used)) static int
gmc_v10_0_vm_fault_interrupt_state(struct amdgpu_device *adev,
				   struct amdgpu_irq_src *src, unsigned type,
				   enum amdgpu_interrupt_state state)
{
	struct amdgpu_vmhub *hub;
	u32 tmp, reg, bits[AMDGPU_MAX_VMHUBS], i;

	bits[AMDGPU_GFXHUB_0] = GCVM_CONTEXT1_CNTL__RANGE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		GCVM_CONTEXT1_CNTL__DUMMY_PAGE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		GCVM_CONTEXT1_CNTL__PDE0_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		GCVM_CONTEXT1_CNTL__VALID_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		GCVM_CONTEXT1_CNTL__READ_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		GCVM_CONTEXT1_CNTL__WRITE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		GCVM_CONTEXT1_CNTL__EXECUTE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK;

	bits[AMDGPU_MMHUB_0] = MMVM_CONTEXT1_CNTL__RANGE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		MMVM_CONTEXT1_CNTL__DUMMY_PAGE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		MMVM_CONTEXT1_CNTL__PDE0_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		MMVM_CONTEXT1_CNTL__VALID_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		MMVM_CONTEXT1_CNTL__READ_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		MMVM_CONTEXT1_CNTL__WRITE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		MMVM_CONTEXT1_CNTL__EXECUTE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK;

	switch (state) {
	case AMDGPU_IRQ_STATE_DISABLE:
		/* MM HUB */
		hub = &adev->vmhub[AMDGPU_MMHUB_0];
		for (i = 0; i < 16; i++) {
			reg = hub->vm_context0_cntl + i;
			tmp = RREG32(reg);
			tmp &= ~bits[AMDGPU_MMHUB_0];
			WREG32(reg, tmp);
		}

		/* GFX HUB */
		hub = &adev->vmhub[AMDGPU_GFXHUB_0];
		for (i = 0; i < 16; i++) {
			reg = hub->vm_context0_cntl + i;
			tmp = RREG32(reg);
			tmp &= ~bits[AMDGPU_GFXHUB_0];
			WREG32(reg, tmp);
		}
		break;
	case AMDGPU_IRQ_STATE_ENABLE:
		/* MM HUB */
		hub = &adev->vmhub[AMDGPU_MMHUB_0];
		for (i = 0; i < 16; i++) {
			reg = hub->vm_context0_cntl + i;
			tmp = RREG32(reg);
			tmp |= bits[AMDGPU_MMHUB_0];
			WREG32(reg, tmp);
		}

		/* GFX HUB */
		hub = &adev->vmhub[AMDGPU_GFXHUB_0];
		for (i = 0; i < 16; i++) {
			reg = hub->vm_context0_cntl + i;
			tmp = RREG32(reg);
			tmp |= bits[AMDGPU_GFXHUB_0];
			WREG32(reg, tmp);
		}
		break;
	default:
		break;
	}

	return 0;
}
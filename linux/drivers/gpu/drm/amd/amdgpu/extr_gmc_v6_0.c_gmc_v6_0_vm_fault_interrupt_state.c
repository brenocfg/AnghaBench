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
struct amdgpu_irq_src {int dummy; } ;
struct amdgpu_device {int dummy; } ;
typedef  enum amdgpu_interrupt_state { ____Placeholder_amdgpu_interrupt_state } amdgpu_interrupt_state ;

/* Variables and functions */
#define  AMDGPU_IRQ_STATE_DISABLE 129 
#define  AMDGPU_IRQ_STATE_ENABLE 128 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int VM_CONTEXT1_CNTL__DUMMY_PAGE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK ; 
 int VM_CONTEXT1_CNTL__PDE0_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK ; 
 int VM_CONTEXT1_CNTL__RANGE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK ; 
 int VM_CONTEXT1_CNTL__READ_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK ; 
 int VM_CONTEXT1_CNTL__VALID_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK ; 
 int VM_CONTEXT1_CNTL__WRITE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmVM_CONTEXT0_CNTL ; 
 int /*<<< orphan*/  mmVM_CONTEXT1_CNTL ; 

__attribute__((used)) static int gmc_v6_0_vm_fault_interrupt_state(struct amdgpu_device *adev,
					     struct amdgpu_irq_src *src,
					     unsigned type,
					     enum amdgpu_interrupt_state state)
{
	u32 tmp;
	u32 bits = (VM_CONTEXT1_CNTL__RANGE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		    VM_CONTEXT1_CNTL__DUMMY_PAGE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		    VM_CONTEXT1_CNTL__PDE0_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		    VM_CONTEXT1_CNTL__VALID_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		    VM_CONTEXT1_CNTL__READ_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		    VM_CONTEXT1_CNTL__WRITE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK);

	switch (state) {
	case AMDGPU_IRQ_STATE_DISABLE:
		tmp = RREG32(mmVM_CONTEXT0_CNTL);
		tmp &= ~bits;
		WREG32(mmVM_CONTEXT0_CNTL, tmp);
		tmp = RREG32(mmVM_CONTEXT1_CNTL);
		tmp &= ~bits;
		WREG32(mmVM_CONTEXT1_CNTL, tmp);
		break;
	case AMDGPU_IRQ_STATE_ENABLE:
		tmp = RREG32(mmVM_CONTEXT0_CNTL);
		tmp |= bits;
		WREG32(mmVM_CONTEXT0_CNTL, tmp);
		tmp = RREG32(mmVM_CONTEXT1_CNTL);
		tmp |= bits;
		WREG32(mmVM_CONTEXT1_CNTL, tmp);
		break;
	default:
		break;
	}

	return 0;
}
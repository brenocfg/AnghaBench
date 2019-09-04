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
 int AMDGPU_IRQ_STATE_DISABLE ; 
 int /*<<< orphan*/  CP_INT_CNTL_RING0 ; 
 int /*<<< orphan*/  PRIV_REG_INT_ENABLE ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gfx_v8_0_set_priv_reg_fault_state(struct amdgpu_device *adev,
					     struct amdgpu_irq_src *source,
					     unsigned type,
					     enum amdgpu_interrupt_state state)
{
	WREG32_FIELD(CP_INT_CNTL_RING0, PRIV_REG_INT_ENABLE,
		     state == AMDGPU_IRQ_STATE_DISABLE ? 0 : 1);

	return 0;
}
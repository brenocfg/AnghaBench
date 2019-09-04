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
 int EINVAL ; 
 int /*<<< orphan*/  SQ_INTERRUPT_MSG_CTRL ; 
 int /*<<< orphan*/  STALL ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gfx_v8_0_set_sq_int_state(struct amdgpu_device *adev,
				     struct amdgpu_irq_src *source,
				     unsigned int type,
				     enum amdgpu_interrupt_state state)
{
	int enable_flag;

	switch (state) {
	case AMDGPU_IRQ_STATE_DISABLE:
		enable_flag = 1;
		break;

	case AMDGPU_IRQ_STATE_ENABLE:
		enable_flag = 0;
		break;

	default:
		return -EINVAL;
	}

	WREG32_FIELD(SQ_INTERRUPT_MSG_CTRL, STALL,
		     enable_flag);

	return 0;
}
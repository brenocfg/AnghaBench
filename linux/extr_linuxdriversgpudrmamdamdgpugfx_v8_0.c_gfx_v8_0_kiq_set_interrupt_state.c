#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct amdgpu_ring {int me; int /*<<< orphan*/  pipe; } ;
struct amdgpu_irq_src {int dummy; } ;
struct TYPE_3__ {struct amdgpu_ring ring; } ;
struct TYPE_4__ {TYPE_1__ kiq; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;
typedef  enum amdgpu_interrupt_state { ____Placeholder_amdgpu_interrupt_state } amdgpu_interrupt_state ;

/* Variables and functions */
#define  AMDGPU_CP_KIQ_IRQ_DRIVER0 128 
 int AMDGPU_IRQ_STATE_DISABLE ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CPC_INT_CNTL ; 
 int /*<<< orphan*/  CP_ME1_PIPE0_INT_CNTL ; 
 int /*<<< orphan*/  CP_ME2_PIPE0_INT_CNTL ; 
 int /*<<< orphan*/  GENERIC2_INT_ENABLE ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gfx_v8_0_kiq_set_interrupt_state(struct amdgpu_device *adev,
					    struct amdgpu_irq_src *src,
					    unsigned int type,
					    enum amdgpu_interrupt_state state)
{
	struct amdgpu_ring *ring = &(adev->gfx.kiq.ring);

	switch (type) {
	case AMDGPU_CP_KIQ_IRQ_DRIVER0:
		WREG32_FIELD(CPC_INT_CNTL, GENERIC2_INT_ENABLE,
			     state == AMDGPU_IRQ_STATE_DISABLE ? 0 : 1);
		if (ring->me == 1)
			WREG32_FIELD_OFFSET(CP_ME1_PIPE0_INT_CNTL,
				     ring->pipe,
				     GENERIC2_INT_ENABLE,
				     state == AMDGPU_IRQ_STATE_DISABLE ? 0 : 1);
		else
			WREG32_FIELD_OFFSET(CP_ME2_PIPE0_INT_CNTL,
				     ring->pipe,
				     GENERIC2_INT_ENABLE,
				     state == AMDGPU_IRQ_STATE_DISABLE ? 0 : 1);
		break;
	default:
		BUG(); /* kiq only support GENERIC2_INT now */
		break;
	}
	return 0;
}
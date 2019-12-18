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
#define  AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE0_EOP 137 
#define  AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE1_EOP 136 
#define  AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE2_EOP 135 
#define  AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE3_EOP 134 
#define  AMDGPU_CP_IRQ_COMPUTE_MEC2_PIPE0_EOP 133 
#define  AMDGPU_CP_IRQ_COMPUTE_MEC2_PIPE1_EOP 132 
#define  AMDGPU_CP_IRQ_COMPUTE_MEC2_PIPE2_EOP 131 
#define  AMDGPU_CP_IRQ_COMPUTE_MEC2_PIPE3_EOP 130 
#define  AMDGPU_CP_IRQ_GFX_ME0_PIPE0_EOP 129 
#define  AMDGPU_CP_IRQ_GFX_ME0_PIPE1_EOP 128 
 int /*<<< orphan*/  gfx_v10_0_set_compute_eop_interrupt_state (struct amdgpu_device*,int,int,int) ; 
 int /*<<< orphan*/  gfx_v10_0_set_gfx_eop_interrupt_state (struct amdgpu_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int gfx_v10_0_set_eop_interrupt_state(struct amdgpu_device *adev,
					    struct amdgpu_irq_src *src,
					    unsigned type,
					    enum amdgpu_interrupt_state state)
{
	switch (type) {
	case AMDGPU_CP_IRQ_GFX_ME0_PIPE0_EOP:
		gfx_v10_0_set_gfx_eop_interrupt_state(adev, 0, 0, state);
		break;
	case AMDGPU_CP_IRQ_GFX_ME0_PIPE1_EOP:
		gfx_v10_0_set_gfx_eop_interrupt_state(adev, 0, 1, state);
		break;
	case AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE0_EOP:
		gfx_v10_0_set_compute_eop_interrupt_state(adev, 1, 0, state);
		break;
	case AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE1_EOP:
		gfx_v10_0_set_compute_eop_interrupt_state(adev, 1, 1, state);
		break;
	case AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE2_EOP:
		gfx_v10_0_set_compute_eop_interrupt_state(adev, 1, 2, state);
		break;
	case AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE3_EOP:
		gfx_v10_0_set_compute_eop_interrupt_state(adev, 1, 3, state);
		break;
	case AMDGPU_CP_IRQ_COMPUTE_MEC2_PIPE0_EOP:
		gfx_v10_0_set_compute_eop_interrupt_state(adev, 2, 0, state);
		break;
	case AMDGPU_CP_IRQ_COMPUTE_MEC2_PIPE1_EOP:
		gfx_v10_0_set_compute_eop_interrupt_state(adev, 2, 1, state);
		break;
	case AMDGPU_CP_IRQ_COMPUTE_MEC2_PIPE2_EOP:
		gfx_v10_0_set_compute_eop_interrupt_state(adev, 2, 2, state);
		break;
	case AMDGPU_CP_IRQ_COMPUTE_MEC2_PIPE3_EOP:
		gfx_v10_0_set_compute_eop_interrupt_state(adev, 2, 3, state);
		break;
	default:
		break;
	}
	return 0;
}
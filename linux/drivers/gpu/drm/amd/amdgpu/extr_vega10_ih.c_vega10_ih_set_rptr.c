#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct amdgpu_ih_ring {int /*<<< orphan*/  rptr; int /*<<< orphan*/  doorbell_index; int /*<<< orphan*/ * rptr_cpu; scalar_t__ use_doorbell; } ;
struct TYPE_2__ {struct amdgpu_ih_ring ih2; struct amdgpu_ih_ring ih1; struct amdgpu_ih_ring ih; } ;
struct amdgpu_device {TYPE_1__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSSSYS ; 
 int /*<<< orphan*/  WDOORBELL32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmIH_RB_RPTR ; 
 int /*<<< orphan*/  mmIH_RB_RPTR_RING1 ; 
 int /*<<< orphan*/  mmIH_RB_RPTR_RING2 ; 
 int /*<<< orphan*/  vega10_ih_irq_rearm (struct amdgpu_device*,struct amdgpu_ih_ring*) ; 

__attribute__((used)) static void vega10_ih_set_rptr(struct amdgpu_device *adev,
			       struct amdgpu_ih_ring *ih)
{
	if (ih->use_doorbell) {
		/* XXX check if swapping is necessary on BE */
		*ih->rptr_cpu = ih->rptr;
		WDOORBELL32(ih->doorbell_index, ih->rptr);

		if (amdgpu_sriov_vf(adev))
			vega10_ih_irq_rearm(adev, ih);
	} else if (ih == &adev->irq.ih) {
		WREG32_SOC15(OSSSYS, 0, mmIH_RB_RPTR, ih->rptr);
	} else if (ih == &adev->irq.ih1) {
		WREG32_SOC15(OSSSYS, 0, mmIH_RB_RPTR_RING1, ih->rptr);
	} else if (ih == &adev->irq.ih2) {
		WREG32_SOC15(OSSSYS, 0, mmIH_RB_RPTR_RING2, ih->rptr);
	}
}
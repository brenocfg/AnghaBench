#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t rptr_offs; int /*<<< orphan*/  rptr; int /*<<< orphan*/  doorbell_index; int /*<<< orphan*/ * ring; scalar_t__ use_bus_addr; scalar_t__ use_doorbell; } ;
struct TYPE_6__ {TYPE_2__ ih; } ;
struct TYPE_4__ {int /*<<< orphan*/ * wb; } ;
struct amdgpu_device {TYPE_3__ irq; TYPE_1__ wb; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSSSYS ; 
 int /*<<< orphan*/  WDOORBELL32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmIH_RB_RPTR ; 

__attribute__((used)) static void vega10_ih_set_rptr(struct amdgpu_device *adev)
{
	if (adev->irq.ih.use_doorbell) {
		/* XXX check if swapping is necessary on BE */
		if (adev->irq.ih.use_bus_addr)
			adev->irq.ih.ring[adev->irq.ih.rptr_offs] = adev->irq.ih.rptr;
		else
			adev->wb.wb[adev->irq.ih.rptr_offs] = adev->irq.ih.rptr;
		WDOORBELL32(adev->irq.ih.doorbell_index, adev->irq.ih.rptr);
	} else {
		WREG32_SOC15(OSSSYS, 0, mmIH_RB_RPTR, adev->irq.ih.rptr);
	}
}
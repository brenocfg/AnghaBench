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
struct TYPE_2__ {unsigned int num_crtc; } ;
struct amdgpu_device {int /*<<< orphan*/  pageflip_irq; TYPE_1__ mode_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_irq_put (struct amdgpu_device*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void dce_v10_0_pageflip_interrupt_fini(struct amdgpu_device *adev)
{
	unsigned i;

	/* Disable pflip interrupts */
	for (i = 0; i < adev->mode_info.num_crtc; i++)
		amdgpu_irq_put(adev, &adev->pageflip_irq, i);
}
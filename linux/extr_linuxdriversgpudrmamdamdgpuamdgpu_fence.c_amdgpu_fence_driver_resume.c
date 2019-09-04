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
struct TYPE_2__ {int /*<<< orphan*/  irq_type; int /*<<< orphan*/  irq_src; int /*<<< orphan*/  initialized; } ;
struct amdgpu_ring {TYPE_1__ fence_drv; } ;
struct amdgpu_device {struct amdgpu_ring** rings; } ;

/* Variables and functions */
 int AMDGPU_MAX_RINGS ; 
 int /*<<< orphan*/  amdgpu_irq_get (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void amdgpu_fence_driver_resume(struct amdgpu_device *adev)
{
	int i;

	for (i = 0; i < AMDGPU_MAX_RINGS; i++) {
		struct amdgpu_ring *ring = adev->rings[i];
		if (!ring || !ring->fence_drv.initialized)
			continue;

		/* enable the interrupt */
		amdgpu_irq_get(adev, ring->fence_drv.irq_src,
			       ring->fence_drv.irq_type);
	}
}
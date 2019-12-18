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
struct amdgpu_iv_entry {int ring_id; } ;
struct amdgpu_irq_src {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * compute_ring; int /*<<< orphan*/ * gfx_ring; } ;
struct amdgpu_device {TYPE_1__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_fence_process (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gfx_v6_0_eop_irq(struct amdgpu_device *adev,
			    struct amdgpu_irq_src *source,
			    struct amdgpu_iv_entry *entry)
{
	switch (entry->ring_id) {
	case 0:
		amdgpu_fence_process(&adev->gfx.gfx_ring[0]);
		break;
	case 1:
	case 2:
		amdgpu_fence_process(&adev->gfx.compute_ring[entry->ring_id - 1]);
		break;
	default:
		break;
	}
	return 0;
}
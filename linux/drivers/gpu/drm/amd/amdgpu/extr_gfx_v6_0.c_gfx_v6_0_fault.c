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
struct amdgpu_ring {int /*<<< orphan*/  sched; } ;
struct amdgpu_iv_entry {int ring_id; } ;
struct TYPE_2__ {struct amdgpu_ring* compute_ring; struct amdgpu_ring* gfx_ring; } ;
struct amdgpu_device {TYPE_1__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_sched_fault (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gfx_v6_0_fault(struct amdgpu_device *adev,
			   struct amdgpu_iv_entry *entry)
{
	struct amdgpu_ring *ring;

	switch (entry->ring_id) {
	case 0:
		ring = &adev->gfx.gfx_ring[0];
		break;
	case 1:
	case 2:
		ring = &adev->gfx.compute_ring[entry->ring_id - 1];
		break;
	default:
		return;
	}
	drm_sched_fault(&ring->sched);
}
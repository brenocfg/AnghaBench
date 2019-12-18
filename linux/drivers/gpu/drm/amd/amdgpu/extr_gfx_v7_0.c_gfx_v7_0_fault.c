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
typedef  int u8 ;
struct amdgpu_ring {int me; int pipe; int /*<<< orphan*/  sched; } ;
struct amdgpu_iv_entry {int ring_id; } ;
struct TYPE_4__ {int num_compute_rings; struct amdgpu_ring* compute_ring; TYPE_1__* gfx_ring; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;
struct TYPE_3__ {int /*<<< orphan*/  sched; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_sched_fault (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gfx_v7_0_fault(struct amdgpu_device *adev,
			   struct amdgpu_iv_entry *entry)
{
	struct amdgpu_ring *ring;
	u8 me_id, pipe_id;
	int i;

	me_id = (entry->ring_id & 0x0c) >> 2;
	pipe_id = (entry->ring_id & 0x03) >> 0;
	switch (me_id) {
	case 0:
		drm_sched_fault(&adev->gfx.gfx_ring[0].sched);
		break;
	case 1:
	case 2:
		for (i = 0; i < adev->gfx.num_compute_rings; i++) {
			ring = &adev->gfx.compute_ring[i];
			if ((ring->me == me_id) && (ring->pipe == pipe_id))
				drm_sched_fault(&ring->sched);
		}
		break;
	}
}
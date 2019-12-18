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
struct TYPE_6__ {int ready; } ;
struct amdgpu_ring {TYPE_3__ sched; } ;
struct amdgpu_kiq {TYPE_1__* pmf; struct amdgpu_ring ring; } ;
struct TYPE_5__ {int num_gfx_rings; int /*<<< orphan*/ * gfx_ring; struct amdgpu_kiq kiq; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;
struct TYPE_4__ {int map_queues_size; int /*<<< orphan*/  (* kiq_map_queues ) (struct amdgpu_ring*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int amdgpu_ring_alloc (struct amdgpu_ring*,int) ; 
 int amdgpu_ring_test_ring (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_ring*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gfx_v10_0_kiq_enable_kgq(struct amdgpu_device *adev)
{
	struct amdgpu_kiq *kiq = &adev->gfx.kiq;
	struct amdgpu_ring *kiq_ring = &adev->gfx.kiq.ring;
	int r, i;

	if (!kiq->pmf || !kiq->pmf->kiq_map_queues)
		return -EINVAL;

	r = amdgpu_ring_alloc(kiq_ring, kiq->pmf->map_queues_size *
					adev->gfx.num_gfx_rings);
	if (r) {
		DRM_ERROR("Failed to lock KIQ (%d).\n", r);
		return r;
	}

	for (i = 0; i < adev->gfx.num_gfx_rings; i++)
		kiq->pmf->kiq_map_queues(kiq_ring, &adev->gfx.gfx_ring[i]);

	r = amdgpu_ring_test_ring(kiq_ring);
	if (r) {
		DRM_ERROR("kfq enable failed\n");
		kiq_ring->sched.ready = false;
	}
	return r;
}
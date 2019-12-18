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
struct TYPE_4__ {int ready; } ;
struct amdgpu_ring {TYPE_2__ sched; int /*<<< orphan*/  mqd_obj; int /*<<< orphan*/ * mqd_ptr; } ;
struct TYPE_3__ {int num_gfx_rings; struct amdgpu_ring* gfx_ring; } ;
struct amdgpu_device {TYPE_1__ gfx; } ;

/* Variables and functions */
 int amdgpu_bo_kmap (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  amdgpu_bo_kunmap (int /*<<< orphan*/ ) ; 
 int amdgpu_bo_reserve (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (int /*<<< orphan*/ ) ; 
 int gfx_v10_0_cp_gfx_start (struct amdgpu_device*) ; 
 int gfx_v10_0_gfx_init_queue (struct amdgpu_ring*) ; 
 int gfx_v10_0_kiq_enable_kgq (struct amdgpu_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int gfx_v10_0_cp_async_gfx_ring_resume(struct amdgpu_device *adev)
{
	int r, i;
	struct amdgpu_ring *ring;

	for (i = 0; i < adev->gfx.num_gfx_rings; i++) {
		ring = &adev->gfx.gfx_ring[i];

		r = amdgpu_bo_reserve(ring->mqd_obj, false);
		if (unlikely(r != 0))
			goto done;

		r = amdgpu_bo_kmap(ring->mqd_obj, (void **)&ring->mqd_ptr);
		if (!r) {
			r = gfx_v10_0_gfx_init_queue(ring);
			amdgpu_bo_kunmap(ring->mqd_obj);
			ring->mqd_ptr = NULL;
		}
		amdgpu_bo_unreserve(ring->mqd_obj);
		if (r)
			goto done;
	}
#ifndef BRING_UP_DEBUG
	r = gfx_v10_0_kiq_enable_kgq(adev);
	if (r)
		goto done;
#endif
	r = gfx_v10_0_cp_gfx_start(adev);
	if (r)
		goto done;

	for (i = 0; i < adev->gfx.num_gfx_rings; i++) {
		ring = &adev->gfx.gfx_ring[i];
		ring->sched.ready = true;
	}
done:
	return r;
}
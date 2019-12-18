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
struct TYPE_4__ {int ready; } ;
struct amdgpu_ring {TYPE_1__ sched; int /*<<< orphan*/  mqd_obj; int /*<<< orphan*/ * mqd_ptr; } ;
struct TYPE_5__ {struct amdgpu_ring ring; } ;
struct TYPE_6__ {TYPE_2__ kiq; } ;
struct amdgpu_device {TYPE_3__ gfx; } ;

/* Variables and functions */
 int amdgpu_bo_kmap (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  amdgpu_bo_kunmap (int /*<<< orphan*/ ) ; 
 int amdgpu_bo_reserve (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfx_v10_0_kiq_init_queue (struct amdgpu_ring*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int gfx_v10_0_kiq_resume(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring;
	int r;

	ring = &adev->gfx.kiq.ring;

	r = amdgpu_bo_reserve(ring->mqd_obj, false);
	if (unlikely(r != 0))
		return r;

	r = amdgpu_bo_kmap(ring->mqd_obj, (void **)&ring->mqd_ptr);
	if (unlikely(r != 0))
		return r;

	gfx_v10_0_kiq_init_queue(ring);
	amdgpu_bo_kunmap(ring->mqd_obj);
	ring->mqd_ptr = NULL;
	amdgpu_bo_unreserve(ring->mqd_obj);
	ring->sched.ready = true;
	return 0;
}
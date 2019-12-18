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
struct amdgpu_ring {int /*<<< orphan*/  mqd_obj; int /*<<< orphan*/ * mqd_ptr; } ;
struct TYPE_2__ {int num_compute_rings; struct amdgpu_ring* compute_ring; } ;
struct amdgpu_device {TYPE_1__ gfx; } ;

/* Variables and functions */
 int amdgpu_bo_kmap (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  amdgpu_bo_kunmap (int /*<<< orphan*/ ) ; 
 int amdgpu_bo_reserve (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (int /*<<< orphan*/ ) ; 
 int amdgpu_gfx_enable_kcq (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v10_0_cp_compute_enable (struct amdgpu_device*,int) ; 
 int gfx_v10_0_kcq_init_queue (struct amdgpu_ring*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int gfx_v10_0_kcq_resume(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring = NULL;
	int r = 0, i;

	gfx_v10_0_cp_compute_enable(adev, true);

	for (i = 0; i < adev->gfx.num_compute_rings; i++) {
		ring = &adev->gfx.compute_ring[i];

		r = amdgpu_bo_reserve(ring->mqd_obj, false);
		if (unlikely(r != 0))
			goto done;
		r = amdgpu_bo_kmap(ring->mqd_obj, (void **)&ring->mqd_ptr);
		if (!r) {
			r = gfx_v10_0_kcq_init_queue(ring);
			amdgpu_bo_kunmap(ring->mqd_obj);
			ring->mqd_ptr = NULL;
		}
		amdgpu_bo_unreserve(ring->mqd_obj);
		if (r)
			goto done;
	}

	r = amdgpu_gfx_enable_kcq(adev);
done:
	return r;
}
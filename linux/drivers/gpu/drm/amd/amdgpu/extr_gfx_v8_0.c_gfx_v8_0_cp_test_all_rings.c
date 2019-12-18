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
struct amdgpu_ring {int dummy; } ;
struct TYPE_4__ {struct amdgpu_ring ring; } ;
struct TYPE_3__ {int num_compute_rings; struct amdgpu_ring* compute_ring; TYPE_2__ kiq; struct amdgpu_ring* gfx_ring; } ;
struct amdgpu_device {TYPE_1__ gfx; } ;

/* Variables and functions */
 int amdgpu_ring_test_helper (struct amdgpu_ring*) ; 

__attribute__((used)) static int gfx_v8_0_cp_test_all_rings(struct amdgpu_device *adev)
{
	int r, i;
	struct amdgpu_ring *ring;

	/* collect all the ring_tests here, gfx, kiq, compute */
	ring = &adev->gfx.gfx_ring[0];
	r = amdgpu_ring_test_helper(ring);
	if (r)
		return r;

	ring = &adev->gfx.kiq.ring;
	r = amdgpu_ring_test_helper(ring);
	if (r)
		return r;

	for (i = 0; i < adev->gfx.num_compute_rings; i++) {
		ring = &adev->gfx.compute_ring[i];
		amdgpu_ring_test_helper(ring);
	}

	return 0;
}
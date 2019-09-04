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
struct amdgpu_ring {int ready; } ;
struct TYPE_2__ {int num_enc_rings; struct amdgpu_ring ring_jpeg; struct amdgpu_ring* ring_enc; struct amdgpu_ring ring_dec; } ;
struct amdgpu_device {TYPE_1__ vcn; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int amdgpu_ring_test_ring (struct amdgpu_ring*) ; 

__attribute__((used)) static int vcn_v1_0_hw_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct amdgpu_ring *ring = &adev->vcn.ring_dec;
	int i, r;

	ring->ready = true;
	r = amdgpu_ring_test_ring(ring);
	if (r) {
		ring->ready = false;
		goto done;
	}

	for (i = 0; i < adev->vcn.num_enc_rings; ++i) {
		ring = &adev->vcn.ring_enc[i];
		ring->ready = true;
		r = amdgpu_ring_test_ring(ring);
		if (r) {
			ring->ready = false;
			goto done;
		}
	}

	ring = &adev->vcn.ring_jpeg;
	ring->ready = true;
	r = amdgpu_ring_test_ring(ring);
	if (r) {
		ring->ready = false;
		goto done;
	}

done:
	if (!r)
		DRM_INFO("VCN decode and encode initialized successfully.\n");

	return r;
}
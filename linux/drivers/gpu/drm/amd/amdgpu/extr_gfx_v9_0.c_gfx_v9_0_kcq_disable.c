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
struct amdgpu_ring {int /*<<< orphan*/  doorbell_index; } ;
struct TYPE_3__ {struct amdgpu_ring ring; } ;
struct TYPE_4__ {int num_compute_rings; struct amdgpu_ring* compute_ring; TYPE_1__ kiq; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_UNMAP_QUEUES ; 
 int PACKET3_UNMAP_QUEUES_ACTION (int) ; 
 int PACKET3_UNMAP_QUEUES_DOORBELL_OFFSET0 (int /*<<< orphan*/ ) ; 
 int PACKET3_UNMAP_QUEUES_ENGINE_SEL (int /*<<< orphan*/ ) ; 
 int PACKET3_UNMAP_QUEUES_NUM_QUEUES (int) ; 
 int PACKET3_UNMAP_QUEUES_QUEUE_SEL (int /*<<< orphan*/ ) ; 
 int amdgpu_ring_alloc (struct amdgpu_ring*,int) ; 
 int amdgpu_ring_test_helper (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 

__attribute__((used)) static int gfx_v9_0_kcq_disable(struct amdgpu_device *adev)
{
	int r, i;
	struct amdgpu_ring *kiq_ring = &adev->gfx.kiq.ring;

	r = amdgpu_ring_alloc(kiq_ring, 6 * adev->gfx.num_compute_rings);
	if (r)
		DRM_ERROR("Failed to lock KIQ (%d).\n", r);

	for (i = 0; i < adev->gfx.num_compute_rings; i++) {
		struct amdgpu_ring *ring = &adev->gfx.compute_ring[i];

		amdgpu_ring_write(kiq_ring, PACKET3(PACKET3_UNMAP_QUEUES, 4));
		amdgpu_ring_write(kiq_ring, /* Q_sel: 0, vmid: 0, engine: 0, num_Q: 1 */
						PACKET3_UNMAP_QUEUES_ACTION(1) | /* RESET_QUEUES */
						PACKET3_UNMAP_QUEUES_QUEUE_SEL(0) |
						PACKET3_UNMAP_QUEUES_ENGINE_SEL(0) |
						PACKET3_UNMAP_QUEUES_NUM_QUEUES(1));
		amdgpu_ring_write(kiq_ring, PACKET3_UNMAP_QUEUES_DOORBELL_OFFSET0(ring->doorbell_index));
		amdgpu_ring_write(kiq_ring, 0);
		amdgpu_ring_write(kiq_ring, 0);
		amdgpu_ring_write(kiq_ring, 0);
	}
	r = amdgpu_ring_test_helper(kiq_ring);
	if (r)
		DRM_ERROR("KCQ disable failed\n");

	return r;
}
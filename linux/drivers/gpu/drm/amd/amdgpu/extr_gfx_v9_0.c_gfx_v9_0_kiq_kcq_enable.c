#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
struct amdgpu_ring {int wptr_offs; int me; int /*<<< orphan*/  doorbell_index; int /*<<< orphan*/  pipe; int /*<<< orphan*/  queue; int /*<<< orphan*/  mqd_obj; } ;
struct TYPE_8__ {unsigned long long gpu_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  queue_bitmap; } ;
struct TYPE_5__ {struct amdgpu_ring ring; } ;
struct TYPE_7__ {int num_compute_rings; struct amdgpu_ring* compute_ring; TYPE_2__ mec; TYPE_1__ kiq; } ;
struct amdgpu_device {TYPE_4__ wb; TYPE_3__ gfx; } ;
typedef  int /*<<< orphan*/  queue_mask ;

/* Variables and functions */
 int AMDGPU_MAX_COMPUTE_QUEUES ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_MAP_QUEUES ; 
 int PACKET3_MAP_QUEUES_ALLOC_FORMAT (int /*<<< orphan*/ ) ; 
 int PACKET3_MAP_QUEUES_DOORBELL_OFFSET (int /*<<< orphan*/ ) ; 
 int PACKET3_MAP_QUEUES_ENGINE_SEL (int /*<<< orphan*/ ) ; 
 int PACKET3_MAP_QUEUES_ME (int) ; 
 int PACKET3_MAP_QUEUES_NUM_QUEUES (int) ; 
 int PACKET3_MAP_QUEUES_PIPE (int /*<<< orphan*/ ) ; 
 int PACKET3_MAP_QUEUES_QUEUE (int /*<<< orphan*/ ) ; 
 int PACKET3_MAP_QUEUES_QUEUE_SEL (int /*<<< orphan*/ ) ; 
 int PACKET3_MAP_QUEUES_QUEUE_TYPE (int /*<<< orphan*/ ) ; 
 int PACKET3_MAP_QUEUES_VMID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACKET3_SET_RESOURCES ; 
 int PACKET3_SET_RESOURCES_QUEUE_TYPE (int /*<<< orphan*/ ) ; 
 int PACKET3_SET_RESOURCES_VMID_MASK (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned long long amdgpu_bo_gpu_offset (int /*<<< orphan*/ ) ; 
 int amdgpu_ring_alloc (struct amdgpu_ring*,int) ; 
 int amdgpu_ring_test_helper (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int lower_32_bits (unsigned long long) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 
 int upper_32_bits (unsigned long long) ; 

__attribute__((used)) static int gfx_v9_0_kiq_kcq_enable(struct amdgpu_device *adev)
{
	struct amdgpu_ring *kiq_ring = &adev->gfx.kiq.ring;
	uint64_t queue_mask = 0;
	int r, i;

	for (i = 0; i < AMDGPU_MAX_COMPUTE_QUEUES; ++i) {
		if (!test_bit(i, adev->gfx.mec.queue_bitmap))
			continue;

		/* This situation may be hit in the future if a new HW
		 * generation exposes more than 64 queues. If so, the
		 * definition of queue_mask needs updating */
		if (WARN_ON(i >= (sizeof(queue_mask)*8))) {
			DRM_ERROR("Invalid KCQ enabled: %d\n", i);
			break;
		}

		queue_mask |= (1ull << i);
	}

	r = amdgpu_ring_alloc(kiq_ring, (7 * adev->gfx.num_compute_rings) + 8);
	if (r) {
		DRM_ERROR("Failed to lock KIQ (%d).\n", r);
		return r;
	}

	/* set resources */
	amdgpu_ring_write(kiq_ring, PACKET3(PACKET3_SET_RESOURCES, 6));
	amdgpu_ring_write(kiq_ring, PACKET3_SET_RESOURCES_VMID_MASK(0) |
			  PACKET3_SET_RESOURCES_QUEUE_TYPE(0));	/* vmid_mask:0 queue_type:0 (KIQ) */
	amdgpu_ring_write(kiq_ring, lower_32_bits(queue_mask));	/* queue mask lo */
	amdgpu_ring_write(kiq_ring, upper_32_bits(queue_mask));	/* queue mask hi */
	amdgpu_ring_write(kiq_ring, 0);	/* gws mask lo */
	amdgpu_ring_write(kiq_ring, 0);	/* gws mask hi */
	amdgpu_ring_write(kiq_ring, 0);	/* oac mask */
	amdgpu_ring_write(kiq_ring, 0);	/* gds heap base:0, gds heap size:0 */
	for (i = 0; i < adev->gfx.num_compute_rings; i++) {
		struct amdgpu_ring *ring = &adev->gfx.compute_ring[i];
		uint64_t mqd_addr = amdgpu_bo_gpu_offset(ring->mqd_obj);
		uint64_t wptr_addr = adev->wb.gpu_addr + (ring->wptr_offs * 4);

		amdgpu_ring_write(kiq_ring, PACKET3(PACKET3_MAP_QUEUES, 5));
		/* Q_sel:0, vmid:0, vidmem: 1, engine:0, num_Q:1*/
		amdgpu_ring_write(kiq_ring, /* Q_sel: 0, vmid: 0, engine: 0, num_Q: 1 */
				  PACKET3_MAP_QUEUES_QUEUE_SEL(0) | /* Queue_Sel */
				  PACKET3_MAP_QUEUES_VMID(0) | /* VMID */
				  PACKET3_MAP_QUEUES_QUEUE(ring->queue) |
				  PACKET3_MAP_QUEUES_PIPE(ring->pipe) |
				  PACKET3_MAP_QUEUES_ME((ring->me == 1 ? 0 : 1)) |
				  PACKET3_MAP_QUEUES_QUEUE_TYPE(0) | /*queue_type: normal compute queue */
				  PACKET3_MAP_QUEUES_ALLOC_FORMAT(0) | /* alloc format: all_on_one_pipe */
				  PACKET3_MAP_QUEUES_ENGINE_SEL(0) | /* engine_sel: compute */
				  PACKET3_MAP_QUEUES_NUM_QUEUES(1)); /* num_queues: must be 1 */
		amdgpu_ring_write(kiq_ring, PACKET3_MAP_QUEUES_DOORBELL_OFFSET(ring->doorbell_index));
		amdgpu_ring_write(kiq_ring, lower_32_bits(mqd_addr));
		amdgpu_ring_write(kiq_ring, upper_32_bits(mqd_addr));
		amdgpu_ring_write(kiq_ring, lower_32_bits(wptr_addr));
		amdgpu_ring_write(kiq_ring, upper_32_bits(wptr_addr));
	}

	r = amdgpu_ring_test_helper(kiq_ring);
	if (r)
		DRM_ERROR("KCQ enable failed\n");

	return r;
}
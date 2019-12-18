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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct amdgpu_ring {int wptr_offs; int me; int /*<<< orphan*/  doorbell_index; int /*<<< orphan*/  pipe; int /*<<< orphan*/  queue; TYPE_2__* funcs; int /*<<< orphan*/  mqd_obj; struct amdgpu_device* adev; } ;
struct TYPE_3__ {scalar_t__ gpu_addr; } ;
struct amdgpu_device {TYPE_1__ wb; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_RING_TYPE_GFX ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_MAP_QUEUES ; 
 int PACKET3_MAP_QUEUES_ALLOC_FORMAT (int /*<<< orphan*/ ) ; 
 int PACKET3_MAP_QUEUES_DOORBELL_OFFSET (int /*<<< orphan*/ ) ; 
 int PACKET3_MAP_QUEUES_ENGINE_SEL (int) ; 
 int PACKET3_MAP_QUEUES_ME (int) ; 
 int PACKET3_MAP_QUEUES_NUM_QUEUES (int) ; 
 int PACKET3_MAP_QUEUES_PIPE (int /*<<< orphan*/ ) ; 
 int PACKET3_MAP_QUEUES_QUEUE (int /*<<< orphan*/ ) ; 
 int PACKET3_MAP_QUEUES_QUEUE_SEL (int /*<<< orphan*/ ) ; 
 int PACKET3_MAP_QUEUES_QUEUE_TYPE (int /*<<< orphan*/ ) ; 
 int PACKET3_MAP_QUEUES_VMID (int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_bo_gpu_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int lower_32_bits (scalar_t__) ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void gfx10_kiq_map_queues(struct amdgpu_ring *kiq_ring,
				 struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = kiq_ring->adev;
	uint64_t mqd_addr = amdgpu_bo_gpu_offset(ring->mqd_obj);
	uint64_t wptr_addr = adev->wb.gpu_addr + (ring->wptr_offs * 4);
	uint32_t eng_sel = ring->funcs->type == AMDGPU_RING_TYPE_GFX ? 4 : 0;

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
			  PACKET3_MAP_QUEUES_ENGINE_SEL(eng_sel) |
			  PACKET3_MAP_QUEUES_NUM_QUEUES(1)); /* num_queues: must be 1 */
	amdgpu_ring_write(kiq_ring, PACKET3_MAP_QUEUES_DOORBELL_OFFSET(ring->doorbell_index));
	amdgpu_ring_write(kiq_ring, lower_32_bits(mqd_addr));
	amdgpu_ring_write(kiq_ring, upper_32_bits(mqd_addr));
	amdgpu_ring_write(kiq_ring, lower_32_bits(wptr_addr));
	amdgpu_ring_write(kiq_ring, upper_32_bits(wptr_addr));
}
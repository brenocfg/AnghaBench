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
typedef  int uint32_t ;
typedef  int u64 ;
struct amdgpu_ring {int /*<<< orphan*/  doorbell_index; TYPE_1__* funcs; } ;
typedef  enum amdgpu_unmap_queues_action { ____Placeholder_amdgpu_unmap_queues_action } amdgpu_unmap_queues_action ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_RING_TYPE_GFX ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_UNMAP_QUEUES ; 
 int PACKET3_UNMAP_QUEUES_ACTION (int) ; 
 int PACKET3_UNMAP_QUEUES_DOORBELL_OFFSET0 (int /*<<< orphan*/ ) ; 
 int PACKET3_UNMAP_QUEUES_ENGINE_SEL (int) ; 
 int PACKET3_UNMAP_QUEUES_NUM_QUEUES (int) ; 
 int PACKET3_UNMAP_QUEUES_QUEUE_SEL (int /*<<< orphan*/ ) ; 
 int PREEMPT_QUEUES_NO_UNMAP ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int lower_32_bits (int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void gfx10_kiq_unmap_queues(struct amdgpu_ring *kiq_ring,
				   struct amdgpu_ring *ring,
				   enum amdgpu_unmap_queues_action action,
				   u64 gpu_addr, u64 seq)
{
	uint32_t eng_sel = ring->funcs->type == AMDGPU_RING_TYPE_GFX ? 4 : 0;

	amdgpu_ring_write(kiq_ring, PACKET3(PACKET3_UNMAP_QUEUES, 4));
	amdgpu_ring_write(kiq_ring, /* Q_sel: 0, vmid: 0, engine: 0, num_Q: 1 */
			  PACKET3_UNMAP_QUEUES_ACTION(action) |
			  PACKET3_UNMAP_QUEUES_QUEUE_SEL(0) |
			  PACKET3_UNMAP_QUEUES_ENGINE_SEL(eng_sel) |
			  PACKET3_UNMAP_QUEUES_NUM_QUEUES(1));
	amdgpu_ring_write(kiq_ring,
		  PACKET3_UNMAP_QUEUES_DOORBELL_OFFSET0(ring->doorbell_index));

	if (action == PREEMPT_QUEUES_NO_UNMAP) {
		amdgpu_ring_write(kiq_ring, lower_32_bits(gpu_addr));
		amdgpu_ring_write(kiq_ring, upper_32_bits(gpu_addr));
		amdgpu_ring_write(kiq_ring, seq);
	} else {
		amdgpu_ring_write(kiq_ring, 0);
		amdgpu_ring_write(kiq_ring, 0);
		amdgpu_ring_write(kiq_ring, 0);
	}
}
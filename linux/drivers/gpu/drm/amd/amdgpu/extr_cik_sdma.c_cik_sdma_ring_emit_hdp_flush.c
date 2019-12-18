#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct amdgpu_ring {scalar_t__ me; } ;

/* Variables and functions */
 int GPU_HDP_FLUSH_DONE__SDMA0_MASK ; 
 int GPU_HDP_FLUSH_DONE__SDMA1_MASK ; 
 int /*<<< orphan*/  SDMA_OPCODE_POLL_REG_MEM ; 
 int SDMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int SDMA_POLL_REG_MEM_EXTRA_FUNC (int) ; 
 int SDMA_POLL_REG_MEM_EXTRA_OP (int) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int mmGPU_HDP_FLUSH_DONE ; 
 int mmGPU_HDP_FLUSH_REQ ; 

__attribute__((used)) static void cik_sdma_ring_emit_hdp_flush(struct amdgpu_ring *ring)
{
	u32 extra_bits = (SDMA_POLL_REG_MEM_EXTRA_OP(1) |
			  SDMA_POLL_REG_MEM_EXTRA_FUNC(3)); /* == */
	u32 ref_and_mask;

	if (ring->me == 0)
		ref_and_mask = GPU_HDP_FLUSH_DONE__SDMA0_MASK;
	else
		ref_and_mask = GPU_HDP_FLUSH_DONE__SDMA1_MASK;

	amdgpu_ring_write(ring, SDMA_PACKET(SDMA_OPCODE_POLL_REG_MEM, 0, extra_bits));
	amdgpu_ring_write(ring, mmGPU_HDP_FLUSH_DONE << 2);
	amdgpu_ring_write(ring, mmGPU_HDP_FLUSH_REQ << 2);
	amdgpu_ring_write(ring, ref_and_mask); /* reference */
	amdgpu_ring_write(ring, ref_and_mask); /* mask */
	amdgpu_ring_write(ring, (0xfff << 16) | 10); /* retry count, poll interval */
}
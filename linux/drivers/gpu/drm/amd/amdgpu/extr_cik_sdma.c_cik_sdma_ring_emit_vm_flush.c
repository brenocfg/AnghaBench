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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int u32 ;
struct amdgpu_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDMA_OPCODE_POLL_REG_MEM ; 
 int SDMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int SDMA_POLL_REG_MEM_EXTRA_FUNC (int /*<<< orphan*/ ) ; 
 int SDMA_POLL_REG_MEM_EXTRA_OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_gmc_emit_flush_gpu_tlb (struct amdgpu_ring*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int mmVM_INVALIDATE_REQUEST ; 

__attribute__((used)) static void cik_sdma_ring_emit_vm_flush(struct amdgpu_ring *ring,
					unsigned vmid, uint64_t pd_addr)
{
	u32 extra_bits = (SDMA_POLL_REG_MEM_EXTRA_OP(0) |
			  SDMA_POLL_REG_MEM_EXTRA_FUNC(0)); /* always */

	amdgpu_gmc_emit_flush_gpu_tlb(ring, vmid, pd_addr);

	amdgpu_ring_write(ring, SDMA_PACKET(SDMA_OPCODE_POLL_REG_MEM, 0, extra_bits));
	amdgpu_ring_write(ring, mmVM_INVALIDATE_REQUEST << 2);
	amdgpu_ring_write(ring, 0);
	amdgpu_ring_write(ring, 0); /* reference */
	amdgpu_ring_write(ring, 0); /* mask */
	amdgpu_ring_write(ring, (0xfff << 16) | 10); /* retry count, poll interval */
}
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
struct amdgpu_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDMA_OP_POLL_REGMEM ; 
 int SDMA_PKT_HEADER_OP (int /*<<< orphan*/ ) ; 
 int SDMA_PKT_POLL_REGMEM_DW5_INTERVAL (int) ; 
 int SDMA_PKT_POLL_REGMEM_DW5_RETRY_COUNT (int) ; 
 int SDMA_PKT_POLL_REGMEM_HEADER_FUNC (int /*<<< orphan*/ ) ; 
 int SDMA_PKT_POLL_REGMEM_HEADER_HDP_FLUSH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_gmc_emit_flush_gpu_tlb (struct amdgpu_ring*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int mmVM_INVALIDATE_REQUEST ; 

__attribute__((used)) static void sdma_v3_0_ring_emit_vm_flush(struct amdgpu_ring *ring,
					 unsigned vmid, uint64_t pd_addr)
{
	amdgpu_gmc_emit_flush_gpu_tlb(ring, vmid, pd_addr);

	/* wait for flush */
	amdgpu_ring_write(ring, SDMA_PKT_HEADER_OP(SDMA_OP_POLL_REGMEM) |
			  SDMA_PKT_POLL_REGMEM_HEADER_HDP_FLUSH(0) |
			  SDMA_PKT_POLL_REGMEM_HEADER_FUNC(0)); /* always */
	amdgpu_ring_write(ring, mmVM_INVALIDATE_REQUEST << 2);
	amdgpu_ring_write(ring, 0);
	amdgpu_ring_write(ring, 0); /* reference */
	amdgpu_ring_write(ring, 0); /* mask */
	amdgpu_ring_write(ring, SDMA_PKT_POLL_REGMEM_DW5_RETRY_COUNT(0xfff) |
			  SDMA_PKT_POLL_REGMEM_DW5_INTERVAL(10)); /* retry count, poll interval */
}
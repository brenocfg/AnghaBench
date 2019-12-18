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
 int DMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_PACKET_POLL_REG_MEM ; 
 int VM_INVALIDATE_REQUEST ; 
 int /*<<< orphan*/  amdgpu_gmc_emit_flush_gpu_tlb (struct amdgpu_ring*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 

__attribute__((used)) static void si_dma_ring_emit_vm_flush(struct amdgpu_ring *ring,
				      unsigned vmid, uint64_t pd_addr)
{
	amdgpu_gmc_emit_flush_gpu_tlb(ring, vmid, pd_addr);

	/* wait for invalidate to complete */
	amdgpu_ring_write(ring, DMA_PACKET(DMA_PACKET_POLL_REG_MEM, 0, 0, 0, 0));
	amdgpu_ring_write(ring, VM_INVALIDATE_REQUEST);
	amdgpu_ring_write(ring, 0xff << 16); /* retry */
	amdgpu_ring_write(ring, 1 << vmid); /* mask */
	amdgpu_ring_write(ring, 0); /* value */
	amdgpu_ring_write(ring, (0 << 28) | 0x20); /* func(always) | poll interval */
}
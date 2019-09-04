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
typedef  int u64 ;
struct amdgpu_ring {int dummy; } ;

/* Variables and functions */
 unsigned int AMDGPU_FENCE_FLAG_64BIT ; 
 int DMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_PACKET_FENCE ; 
 int /*<<< orphan*/  DMA_PACKET_TRAP ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void si_dma_ring_emit_fence(struct amdgpu_ring *ring, u64 addr, u64 seq,
				      unsigned flags)
{

	bool write64bit = flags & AMDGPU_FENCE_FLAG_64BIT;
	/* write the fence */
	amdgpu_ring_write(ring, DMA_PACKET(DMA_PACKET_FENCE, 0, 0, 0, 0));
	amdgpu_ring_write(ring, addr & 0xfffffffc);
	amdgpu_ring_write(ring, (upper_32_bits(addr) & 0xff));
	amdgpu_ring_write(ring, seq);
	/* optionally write high bits as well */
	if (write64bit) {
		addr += 4;
		amdgpu_ring_write(ring, DMA_PACKET(DMA_PACKET_FENCE, 0, 0, 0, 0));
		amdgpu_ring_write(ring, addr & 0xfffffffc);
		amdgpu_ring_write(ring, (upper_32_bits(addr) & 0xff));
		amdgpu_ring_write(ring, upper_32_bits(seq));
	}
	/* generate an interrupt */
	amdgpu_ring_write(ring, DMA_PACKET(DMA_PACKET_TRAP, 0, 0, 0, 0));
}
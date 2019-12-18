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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_ring {int /*<<< orphan*/  wptr; } ;
struct amdgpu_job {int dummy; } ;
struct amdgpu_ib {int gpu_addr; int length_dw; } ;

/* Variables and functions */
 unsigned int AMDGPU_JOB_GET_VMID (struct amdgpu_job*) ; 
 int DMA_IB_PACKET (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int DMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_PACKET_INDIRECT_BUFFER ; 
 int /*<<< orphan*/  DMA_PACKET_NOP ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void si_dma_ring_emit_ib(struct amdgpu_ring *ring,
				struct amdgpu_job *job,
				struct amdgpu_ib *ib,
				uint32_t flags)
{
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);
	/* The indirect buffer packet must end on an 8 DW boundary in the DMA ring.
	 * Pad as necessary with NOPs.
	 */
	while ((lower_32_bits(ring->wptr) & 7) != 5)
		amdgpu_ring_write(ring, DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0, 0));
	amdgpu_ring_write(ring, DMA_IB_PACKET(DMA_PACKET_INDIRECT_BUFFER, vmid, 0));
	amdgpu_ring_write(ring, (ib->gpu_addr & 0xFFFFFFE0));
	amdgpu_ring_write(ring, (ib->length_dw << 12) | (upper_32_bits(ib->gpu_addr) & 0xFF));

}
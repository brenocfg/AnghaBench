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
typedef  unsigned int u32 ;
struct amdgpu_ring {int /*<<< orphan*/  wptr; } ;
struct amdgpu_job {int dummy; } ;
struct amdgpu_ib {int gpu_addr; int length_dw; } ;

/* Variables and functions */
 unsigned int AMDGPU_JOB_GET_VMID (struct amdgpu_job*) ; 
 int /*<<< orphan*/  SDMA_OPCODE_INDIRECT_BUFFER ; 
 int SDMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  cik_sdma_ring_insert_nop (struct amdgpu_ring*,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void cik_sdma_ring_emit_ib(struct amdgpu_ring *ring,
				  struct amdgpu_job *job,
				  struct amdgpu_ib *ib,
				  uint32_t flags)
{
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);
	u32 extra_bits = vmid & 0xf;

	/* IB packet must end on a 8 DW boundary */
	cik_sdma_ring_insert_nop(ring, (12 - (lower_32_bits(ring->wptr) & 7)) % 8);

	amdgpu_ring_write(ring, SDMA_PACKET(SDMA_OPCODE_INDIRECT_BUFFER, 0, extra_bits));
	amdgpu_ring_write(ring, ib->gpu_addr & 0xffffffe0); /* base must be 32 byte aligned */
	amdgpu_ring_write(ring, upper_32_bits(ib->gpu_addr) & 0xffffffff);
	amdgpu_ring_write(ring, ib->length_dw);

}
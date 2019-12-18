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
struct amdgpu_ib {int length_dw; int /*<<< orphan*/  gpu_addr; } ;

/* Variables and functions */
 unsigned int AMDGPU_JOB_GET_VMID (struct amdgpu_job*) ; 
 int /*<<< orphan*/  SDMA_OP_INDIRECT ; 
 int SDMA_PKT_HEADER_OP (int /*<<< orphan*/ ) ; 
 int SDMA_PKT_INDIRECT_HEADER_VMID (unsigned int) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_v2_4_ring_insert_nop (struct amdgpu_ring*,int) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdma_v2_4_ring_emit_ib(struct amdgpu_ring *ring,
				   struct amdgpu_job *job,
				   struct amdgpu_ib *ib,
				   uint32_t flags)
{
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);

	/* IB packet must end on a 8 DW boundary */
	sdma_v2_4_ring_insert_nop(ring, (10 - (lower_32_bits(ring->wptr) & 7)) % 8);

	amdgpu_ring_write(ring, SDMA_PKT_HEADER_OP(SDMA_OP_INDIRECT) |
			  SDMA_PKT_INDIRECT_HEADER_VMID(vmid & 0xf));
	/* base must be 32 byte aligned */
	amdgpu_ring_write(ring, lower_32_bits(ib->gpu_addr) & 0xffffffe0);
	amdgpu_ring_write(ring, upper_32_bits(ib->gpu_addr));
	amdgpu_ring_write(ring, ib->length_dw);
	amdgpu_ring_write(ring, 0);
	amdgpu_ring_write(ring, 0);

}
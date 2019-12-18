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
typedef  int uint32_t ;
struct amdgpu_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDMA_OP_POLL_REGMEM ; 
 int SDMA_PKT_HEADER_OP (int /*<<< orphan*/ ) ; 
 int SDMA_PKT_POLL_REGMEM_DW5_INTERVAL (int) ; 
 int SDMA_PKT_POLL_REGMEM_DW5_RETRY_COUNT (int) ; 
 int SDMA_PKT_POLL_REGMEM_HEADER_FUNC (int) ; 
 int SDMA_PKT_POLL_REGMEM_HEADER_HDP_FLUSH (int) ; 
 int SDMA_PKT_POLL_REGMEM_HEADER_MEM_POLL (int) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 

__attribute__((used)) static void sdma_v4_0_wait_reg_mem(struct amdgpu_ring *ring,
				   int mem_space, int hdp,
				   uint32_t addr0, uint32_t addr1,
				   uint32_t ref, uint32_t mask,
				   uint32_t inv)
{
	amdgpu_ring_write(ring, SDMA_PKT_HEADER_OP(SDMA_OP_POLL_REGMEM) |
			  SDMA_PKT_POLL_REGMEM_HEADER_HDP_FLUSH(hdp) |
			  SDMA_PKT_POLL_REGMEM_HEADER_MEM_POLL(mem_space) |
			  SDMA_PKT_POLL_REGMEM_HEADER_FUNC(3)); /* == */
	if (mem_space) {
		/* memory */
		amdgpu_ring_write(ring, addr0);
		amdgpu_ring_write(ring, addr1);
	} else {
		/* registers */
		amdgpu_ring_write(ring, addr0 << 2);
		amdgpu_ring_write(ring, addr1 << 2);
	}
	amdgpu_ring_write(ring, ref); /* reference */
	amdgpu_ring_write(ring, mask); /* mask */
	amdgpu_ring_write(ring, SDMA_PKT_POLL_REGMEM_DW5_RETRY_COUNT(0xfff) |
			  SDMA_PKT_POLL_REGMEM_DW5_INTERVAL(inv)); /* retry count, poll interval */
}
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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int sync_seq; int gpu_addr; } ;
struct amdgpu_ring {TYPE_1__ fence_drv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDMA_OP_POLL_REGMEM ; 
 int SDMA_PKT_HEADER_OP (int /*<<< orphan*/ ) ; 
 int SDMA_PKT_POLL_REGMEM_DW5_INTERVAL (int) ; 
 int SDMA_PKT_POLL_REGMEM_DW5_RETRY_COUNT (int) ; 
 int SDMA_PKT_POLL_REGMEM_HEADER_FUNC (int) ; 
 int SDMA_PKT_POLL_REGMEM_HEADER_HDP_FLUSH (int /*<<< orphan*/ ) ; 
 int SDMA_PKT_POLL_REGMEM_HEADER_MEM_POLL (int) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void sdma_v2_4_ring_emit_pipeline_sync(struct amdgpu_ring *ring)
{
	uint32_t seq = ring->fence_drv.sync_seq;
	uint64_t addr = ring->fence_drv.gpu_addr;

	/* wait for idle */
	amdgpu_ring_write(ring, SDMA_PKT_HEADER_OP(SDMA_OP_POLL_REGMEM) |
			  SDMA_PKT_POLL_REGMEM_HEADER_HDP_FLUSH(0) |
			  SDMA_PKT_POLL_REGMEM_HEADER_FUNC(3) | /* equal */
			  SDMA_PKT_POLL_REGMEM_HEADER_MEM_POLL(1));
	amdgpu_ring_write(ring, addr & 0xfffffffc);
	amdgpu_ring_write(ring, upper_32_bits(addr) & 0xffffffff);
	amdgpu_ring_write(ring, seq); /* reference */
	amdgpu_ring_write(ring, 0xffffffff); /* mask */
	amdgpu_ring_write(ring, SDMA_PKT_POLL_REGMEM_DW5_RETRY_COUNT(0xfff) |
			  SDMA_PKT_POLL_REGMEM_DW5_INTERVAL(4)); /* retry count, poll interval */
}
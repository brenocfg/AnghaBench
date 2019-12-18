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
 int SDMA_PKT_POLL_REGMEM_HEADER_HDP_FLUSH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 

__attribute__((used)) static void sdma_v5_0_ring_emit_reg_wait(struct amdgpu_ring *ring, uint32_t reg,
					 uint32_t val, uint32_t mask)
{
	amdgpu_ring_write(ring, SDMA_PKT_HEADER_OP(SDMA_OP_POLL_REGMEM) |
			  SDMA_PKT_POLL_REGMEM_HEADER_HDP_FLUSH(0) |
			  SDMA_PKT_POLL_REGMEM_HEADER_FUNC(3)); /* equal */
	amdgpu_ring_write(ring, reg << 2);
	amdgpu_ring_write(ring, 0);
	amdgpu_ring_write(ring, val); /* reference */
	amdgpu_ring_write(ring, mask); /* mask */
	amdgpu_ring_write(ring, SDMA_PKT_POLL_REGMEM_DW5_RETRY_COUNT(0xfff) |
			  SDMA_PKT_POLL_REGMEM_DW5_INTERVAL(10));
}
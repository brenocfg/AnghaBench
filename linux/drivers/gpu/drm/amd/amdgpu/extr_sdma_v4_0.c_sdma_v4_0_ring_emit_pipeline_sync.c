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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int gpu_addr; int /*<<< orphan*/  sync_seq; } ;
struct amdgpu_ring {TYPE_1__ fence_drv; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdma_v4_0_wait_reg_mem (struct amdgpu_ring*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void sdma_v4_0_ring_emit_pipeline_sync(struct amdgpu_ring *ring)
{
	uint32_t seq = ring->fence_drv.sync_seq;
	uint64_t addr = ring->fence_drv.gpu_addr;

	/* wait for idle */
	sdma_v4_0_wait_reg_mem(ring, 1, 0,
			       addr & 0xfffffffc,
			       upper_32_bits(addr) & 0xffffffff,
			       seq, 0xffffffff, 4);
}
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
typedef  int /*<<< orphan*/  u64 ;
struct radeon_ring {int dummy; } ;
struct radeon_fence {size_t ring; int /*<<< orphan*/  seq; } ;
struct radeon_device {TYPE_1__* fence_drv; struct radeon_ring* ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpu_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDMA_OPCODE_FENCE ; 
 int /*<<< orphan*/  SDMA_OPCODE_TRAP ; 
 int /*<<< orphan*/  SDMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cik_sdma_hdp_flush_ring_emit (struct radeon_device*,size_t) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

void cik_sdma_fence_ring_emit(struct radeon_device *rdev,
			      struct radeon_fence *fence)
{
	struct radeon_ring *ring = &rdev->ring[fence->ring];
	u64 addr = rdev->fence_drv[fence->ring].gpu_addr;

	/* write the fence */
	radeon_ring_write(ring, SDMA_PACKET(SDMA_OPCODE_FENCE, 0, 0));
	radeon_ring_write(ring, lower_32_bits(addr));
	radeon_ring_write(ring, upper_32_bits(addr));
	radeon_ring_write(ring, fence->seq);
	/* generate an interrupt */
	radeon_ring_write(ring, SDMA_PACKET(SDMA_OPCODE_TRAP, 0, 0));
	/* flush HDP */
	cik_sdma_hdp_flush_ring_emit(rdev, fence->ring);
}
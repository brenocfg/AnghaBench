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
typedef  int u64 ;
struct radeon_ring {int dummy; } ;
struct radeon_fence {size_t ring; int seq; } ;
struct radeon_device {TYPE_1__* fence_drv; struct radeon_ring* ring; } ;
struct TYPE_2__ {int gpu_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_FLUSH_AND_INV_TS_EVENT ; 
 int DATA_SEL (int) ; 
 int EOP_TCL1_ACTION_EN ; 
 int EOP_TC_ACTION_EN ; 
 int EVENT_INDEX (int) ; 
 int EVENT_TYPE (int /*<<< orphan*/ ) ; 
 int INT_SEL (int) ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_RELEASE_MEM ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 
 int upper_32_bits (int) ; 

void cik_fence_compute_ring_emit(struct radeon_device *rdev,
				 struct radeon_fence *fence)
{
	struct radeon_ring *ring = &rdev->ring[fence->ring];
	u64 addr = rdev->fence_drv[fence->ring].gpu_addr;

	/* RELEASE_MEM - flush caches, send int */
	radeon_ring_write(ring, PACKET3(PACKET3_RELEASE_MEM, 5));
	radeon_ring_write(ring, (EOP_TCL1_ACTION_EN |
				 EOP_TC_ACTION_EN |
				 EVENT_TYPE(CACHE_FLUSH_AND_INV_TS_EVENT) |
				 EVENT_INDEX(5)));
	radeon_ring_write(ring, DATA_SEL(1) | INT_SEL(2));
	radeon_ring_write(ring, addr & 0xfffffffc);
	radeon_ring_write(ring, upper_32_bits(addr));
	radeon_ring_write(ring, fence->seq);
	radeon_ring_write(ring, 0);
}
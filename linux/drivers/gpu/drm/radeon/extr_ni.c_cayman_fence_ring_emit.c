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
typedef  int u32 ;
struct radeon_ring {int dummy; } ;
struct radeon_fence {size_t ring; int seq; } ;
struct radeon_device {TYPE_1__* fence_drv; struct radeon_ring* ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpu_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_FLUSH_AND_INV_EVENT_TS ; 
 int DATA_SEL (int) ; 
 int EVENT_INDEX (int) ; 
 int EVENT_TYPE (int /*<<< orphan*/ ) ; 
 int INT_SEL (int) ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int PACKET3_ENGINE_ME ; 
 int /*<<< orphan*/  PACKET3_EVENT_WRITE_EOP ; 
 int PACKET3_FULL_CACHE_ENA ; 
 int PACKET3_SH_ACTION_ENA ; 
 int /*<<< orphan*/  PACKET3_SURFACE_SYNC ; 
 int PACKET3_TC_ACTION_ENA ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

void cayman_fence_ring_emit(struct radeon_device *rdev,
			    struct radeon_fence *fence)
{
	struct radeon_ring *ring = &rdev->ring[fence->ring];
	u64 addr = rdev->fence_drv[fence->ring].gpu_addr;
	u32 cp_coher_cntl = PACKET3_FULL_CACHE_ENA | PACKET3_TC_ACTION_ENA |
		PACKET3_SH_ACTION_ENA;

	/* flush read cache over gart for this vmid */
	radeon_ring_write(ring, PACKET3(PACKET3_SURFACE_SYNC, 3));
	radeon_ring_write(ring, PACKET3_ENGINE_ME | cp_coher_cntl);
	radeon_ring_write(ring, 0xFFFFFFFF);
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, 10); /* poll interval */
	/* EVENT_WRITE_EOP - flush caches, send int */
	radeon_ring_write(ring, PACKET3(PACKET3_EVENT_WRITE_EOP, 4));
	radeon_ring_write(ring, EVENT_TYPE(CACHE_FLUSH_AND_INV_EVENT_TS) | EVENT_INDEX(5));
	radeon_ring_write(ring, lower_32_bits(addr));
	radeon_ring_write(ring, (upper_32_bits(addr) & 0xff) | DATA_SEL(1) | INT_SEL(2));
	radeon_ring_write(ring, fence->seq);
	radeon_ring_write(ring, 0);
}
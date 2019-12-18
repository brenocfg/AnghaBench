#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct radeon_ring {int dummy; } ;
struct radeon_fence {size_t ring; int seq; } ;
struct TYPE_3__ {scalar_t__ use_event; } ;
struct radeon_device {scalar_t__ family; TYPE_2__* fence_drv; TYPE_1__ wb; struct radeon_ring* ring; } ;
struct TYPE_4__ {int scratch_reg; int /*<<< orphan*/  gpu_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_FLUSH_AND_INV_EVENT ; 
 int /*<<< orphan*/  CACHE_FLUSH_AND_INV_EVENT_TS ; 
 scalar_t__ CHIP_RV770 ; 
 int /*<<< orphan*/  CP_INT_STATUS ; 
 int DATA_SEL (int) ; 
 int EVENT_INDEX (int) ; 
 int EVENT_TYPE (int /*<<< orphan*/ ) ; 
 int INT_SEL (int) ; 
 int PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_EVENT_WRITE ; 
 int /*<<< orphan*/  PACKET3_EVENT_WRITE_EOP ; 
 int PACKET3_FULL_CACHE_ENA ; 
 int /*<<< orphan*/  PACKET3_SET_CONFIG_REG ; 
 int PACKET3_SET_CONFIG_REG_OFFSET ; 
 int PACKET3_SH_ACTION_ENA ; 
 int /*<<< orphan*/  PACKET3_SURFACE_SYNC ; 
 int PACKET3_TC_ACTION_ENA ; 
 int PACKET3_VC_ACTION_ENA ; 
 int RB_INT_STAT ; 
 int WAIT_3D_IDLECLEAN_bit ; 
 int WAIT_3D_IDLE_bit ; 
 int WAIT_UNTIL ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

void r600_fence_ring_emit(struct radeon_device *rdev,
			  struct radeon_fence *fence)
{
	struct radeon_ring *ring = &rdev->ring[fence->ring];
	u32 cp_coher_cntl = PACKET3_TC_ACTION_ENA | PACKET3_VC_ACTION_ENA |
		PACKET3_SH_ACTION_ENA;

	if (rdev->family >= CHIP_RV770)
		cp_coher_cntl |= PACKET3_FULL_CACHE_ENA;

	if (rdev->wb.use_event) {
		u64 addr = rdev->fence_drv[fence->ring].gpu_addr;
		/* flush read cache over gart */
		radeon_ring_write(ring, PACKET3(PACKET3_SURFACE_SYNC, 3));
		radeon_ring_write(ring, cp_coher_cntl);
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
	} else {
		/* flush read cache over gart */
		radeon_ring_write(ring, PACKET3(PACKET3_SURFACE_SYNC, 3));
		radeon_ring_write(ring, cp_coher_cntl);
		radeon_ring_write(ring, 0xFFFFFFFF);
		radeon_ring_write(ring, 0);
		radeon_ring_write(ring, 10); /* poll interval */
		radeon_ring_write(ring, PACKET3(PACKET3_EVENT_WRITE, 0));
		radeon_ring_write(ring, EVENT_TYPE(CACHE_FLUSH_AND_INV_EVENT) | EVENT_INDEX(0));
		/* wait for 3D idle clean */
		radeon_ring_write(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
		radeon_ring_write(ring, (WAIT_UNTIL - PACKET3_SET_CONFIG_REG_OFFSET) >> 2);
		radeon_ring_write(ring, WAIT_3D_IDLE_bit | WAIT_3D_IDLECLEAN_bit);
		/* Emit fence sequence & fire IRQ */
		radeon_ring_write(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
		radeon_ring_write(ring, ((rdev->fence_drv[fence->ring].scratch_reg - PACKET3_SET_CONFIG_REG_OFFSET) >> 2));
		radeon_ring_write(ring, fence->seq);
		/* CP_INTERRUPT packet 3 no longer exists, use packet 0 */
		radeon_ring_write(ring, PACKET0(CP_INT_STATUS, 0));
		radeon_ring_write(ring, RB_INT_STAT);
	}
}
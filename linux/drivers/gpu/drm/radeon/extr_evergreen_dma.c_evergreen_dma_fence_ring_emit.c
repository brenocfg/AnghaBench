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
 int DMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_PACKET_FENCE ; 
 int /*<<< orphan*/  DMA_PACKET_SRBM_WRITE ; 
 int /*<<< orphan*/  DMA_PACKET_TRAP ; 
 int HDP_MEM_COHERENCY_FLUSH_CNTL ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 
 int upper_32_bits (int) ; 

void evergreen_dma_fence_ring_emit(struct radeon_device *rdev,
				   struct radeon_fence *fence)
{
	struct radeon_ring *ring = &rdev->ring[fence->ring];
	u64 addr = rdev->fence_drv[fence->ring].gpu_addr;
	/* write the fence */
	radeon_ring_write(ring, DMA_PACKET(DMA_PACKET_FENCE, 0, 0));
	radeon_ring_write(ring, addr & 0xfffffffc);
	radeon_ring_write(ring, (upper_32_bits(addr) & 0xff));
	radeon_ring_write(ring, fence->seq);
	/* generate an interrupt */
	radeon_ring_write(ring, DMA_PACKET(DMA_PACKET_TRAP, 0, 0));
	/* flush HDP */
	radeon_ring_write(ring, DMA_PACKET(DMA_PACKET_SRBM_WRITE, 0, 0));
	radeon_ring_write(ring, (0xf << 16) | (HDP_MEM_COHERENCY_FLUSH_CNTL >> 2));
	radeon_ring_write(ring, 1);
}
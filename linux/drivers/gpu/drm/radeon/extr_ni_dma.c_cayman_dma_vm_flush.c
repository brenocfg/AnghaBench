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
typedef  int uint64_t ;
struct radeon_ring {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int DMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_PACKET_SRBM_WRITE ; 
 int DMA_SRBM_READ_PACKET ; 
 int HDP_MEM_COHERENCY_FLUSH_CNTL ; 
 unsigned int VM_CONTEXT0_PAGE_TABLE_BASE_ADDR ; 
 int VM_INVALIDATE_REQUEST ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 

void cayman_dma_vm_flush(struct radeon_device *rdev, struct radeon_ring *ring,
			 unsigned vm_id, uint64_t pd_addr)
{
	radeon_ring_write(ring, DMA_PACKET(DMA_PACKET_SRBM_WRITE, 0, 0, 0));
	radeon_ring_write(ring, (0xf << 16) | ((VM_CONTEXT0_PAGE_TABLE_BASE_ADDR + (vm_id << 2)) >> 2));
	radeon_ring_write(ring, pd_addr >> 12);

	/* flush hdp cache */
	radeon_ring_write(ring, DMA_PACKET(DMA_PACKET_SRBM_WRITE, 0, 0, 0));
	radeon_ring_write(ring, (0xf << 16) | (HDP_MEM_COHERENCY_FLUSH_CNTL >> 2));
	radeon_ring_write(ring, 1);

	/* bits 0-7 are the VM contexts0-7 */
	radeon_ring_write(ring, DMA_PACKET(DMA_PACKET_SRBM_WRITE, 0, 0, 0));
	radeon_ring_write(ring, (0xf << 16) | (VM_INVALIDATE_REQUEST >> 2));
	radeon_ring_write(ring, 1 << vm_id);

	/* wait for invalidate to complete */
	radeon_ring_write(ring, DMA_SRBM_READ_PACKET);
	radeon_ring_write(ring, (0xff << 20) | (VM_INVALIDATE_REQUEST >> 2));
	radeon_ring_write(ring, 0); /* mask */
	radeon_ring_write(ring, 0); /* value */
}
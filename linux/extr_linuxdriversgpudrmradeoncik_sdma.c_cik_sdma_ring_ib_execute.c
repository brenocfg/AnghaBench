#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct radeon_ring {int wptr; int next_rptr_gpu_addr; } ;
struct radeon_ib {size_t ring; int gpu_addr; int length_dw; TYPE_2__* vm; } ;
struct TYPE_6__ {scalar_t__ enabled; } ;
struct radeon_device {TYPE_3__ wb; struct radeon_ring* ring; } ;
struct TYPE_5__ {TYPE_1__* ids; } ;
struct TYPE_4__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDMA_OPCODE_INDIRECT_BUFFER ; 
 int /*<<< orphan*/  SDMA_OPCODE_NOP ; 
 int /*<<< orphan*/  SDMA_OPCODE_WRITE ; 
 int SDMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDMA_WRITE_SUB_OPCODE_LINEAR ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 
 int upper_32_bits (int) ; 

void cik_sdma_ring_ib_execute(struct radeon_device *rdev,
			      struct radeon_ib *ib)
{
	struct radeon_ring *ring = &rdev->ring[ib->ring];
	u32 extra_bits = (ib->vm ? ib->vm->ids[ib->ring].id : 0) & 0xf;

	if (rdev->wb.enabled) {
		u32 next_rptr = ring->wptr + 5;
		while ((next_rptr & 7) != 4)
			next_rptr++;
		next_rptr += 4;
		radeon_ring_write(ring, SDMA_PACKET(SDMA_OPCODE_WRITE, SDMA_WRITE_SUB_OPCODE_LINEAR, 0));
		radeon_ring_write(ring, ring->next_rptr_gpu_addr & 0xfffffffc);
		radeon_ring_write(ring, upper_32_bits(ring->next_rptr_gpu_addr));
		radeon_ring_write(ring, 1); /* number of DWs to follow */
		radeon_ring_write(ring, next_rptr);
	}

	/* IB packet must end on a 8 DW boundary */
	while ((ring->wptr & 7) != 4)
		radeon_ring_write(ring, SDMA_PACKET(SDMA_OPCODE_NOP, 0, 0));
	radeon_ring_write(ring, SDMA_PACKET(SDMA_OPCODE_INDIRECT_BUFFER, 0, extra_bits));
	radeon_ring_write(ring, ib->gpu_addr & 0xffffffe0); /* base must be 32 byte aligned */
	radeon_ring_write(ring, upper_32_bits(ib->gpu_addr));
	radeon_ring_write(ring, ib->length_dw);

}
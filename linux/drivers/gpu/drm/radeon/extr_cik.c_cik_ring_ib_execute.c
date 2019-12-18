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
typedef  unsigned int u32 ;
struct radeon_ring {int rptr_save_reg; int wptr; int next_rptr_gpu_addr; } ;
struct radeon_ib {size_t ring; unsigned int length_dw; int gpu_addr; scalar_t__ is_const_ib; TYPE_2__* vm; } ;
struct TYPE_6__ {scalar_t__ enabled; } ;
struct radeon_device {TYPE_3__ wb; struct radeon_ring* ring; } ;
struct TYPE_5__ {TYPE_1__* ids; } ;
struct TYPE_4__ {unsigned int id; } ;

/* Variables and functions */
 unsigned int INDIRECT_BUFFER_VALID ; 
 unsigned int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_INDIRECT_BUFFER ; 
 int /*<<< orphan*/  PACKET3_INDIRECT_BUFFER_CONST ; 
 int /*<<< orphan*/  PACKET3_SET_UCONFIG_REG ; 
 int PACKET3_SET_UCONFIG_REG_START ; 
 int /*<<< orphan*/  PACKET3_SWITCH_BUFFER ; 
 int /*<<< orphan*/  PACKET3_WRITE_DATA ; 
 unsigned int WRITE_DATA_DST_SEL (int) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,unsigned int) ; 
 int upper_32_bits (int) ; 

void cik_ring_ib_execute(struct radeon_device *rdev, struct radeon_ib *ib)
{
	struct radeon_ring *ring = &rdev->ring[ib->ring];
	unsigned vm_id = ib->vm ? ib->vm->ids[ib->ring].id : 0;
	u32 header, control = INDIRECT_BUFFER_VALID;

	if (ib->is_const_ib) {
		/* set switch buffer packet before const IB */
		radeon_ring_write(ring, PACKET3(PACKET3_SWITCH_BUFFER, 0));
		radeon_ring_write(ring, 0);

		header = PACKET3(PACKET3_INDIRECT_BUFFER_CONST, 2);
	} else {
		u32 next_rptr;
		if (ring->rptr_save_reg) {
			next_rptr = ring->wptr + 3 + 4;
			radeon_ring_write(ring, PACKET3(PACKET3_SET_UCONFIG_REG, 1));
			radeon_ring_write(ring, ((ring->rptr_save_reg -
						  PACKET3_SET_UCONFIG_REG_START) >> 2));
			radeon_ring_write(ring, next_rptr);
		} else if (rdev->wb.enabled) {
			next_rptr = ring->wptr + 5 + 4;
			radeon_ring_write(ring, PACKET3(PACKET3_WRITE_DATA, 3));
			radeon_ring_write(ring, WRITE_DATA_DST_SEL(1));
			radeon_ring_write(ring, ring->next_rptr_gpu_addr & 0xfffffffc);
			radeon_ring_write(ring, upper_32_bits(ring->next_rptr_gpu_addr));
			radeon_ring_write(ring, next_rptr);
		}

		header = PACKET3(PACKET3_INDIRECT_BUFFER, 2);
	}

	control |= ib->length_dw | (vm_id << 24);

	radeon_ring_write(ring, header);
	radeon_ring_write(ring, (ib->gpu_addr & 0xFFFFFFFC));
	radeon_ring_write(ring, upper_32_bits(ib->gpu_addr) & 0xFFFF);
	radeon_ring_write(ring, control);
}
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
struct radeon_ring {int rptr_save_reg; int wptr; int next_rptr_gpu_addr; } ;
struct radeon_ib {size_t ring; int gpu_addr; unsigned int length_dw; scalar_t__ is_const_ib; TYPE_2__* vm; } ;
struct TYPE_6__ {scalar_t__ enabled; } ;
struct radeon_device {TYPE_3__ wb; struct radeon_ring* ring; } ;
struct TYPE_5__ {TYPE_1__* ids; } ;
struct TYPE_4__ {unsigned int id; } ;

/* Variables and functions */
 int CP_COHER_CNTL2 ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_INDIRECT_BUFFER ; 
 int /*<<< orphan*/  PACKET3_INDIRECT_BUFFER_CONST ; 
 int /*<<< orphan*/  PACKET3_SET_CONFIG_REG ; 
 int PACKET3_SET_CONFIG_REG_START ; 
 int PACKET3_SH_ICACHE_ACTION_ENA ; 
 int PACKET3_SH_KCACHE_ACTION_ENA ; 
 int /*<<< orphan*/  PACKET3_SURFACE_SYNC ; 
 int /*<<< orphan*/  PACKET3_SWITCH_BUFFER ; 
 int PACKET3_TCL1_ACTION_ENA ; 
 int PACKET3_TC_ACTION_ENA ; 
 int /*<<< orphan*/  PACKET3_WRITE_DATA ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 
 int upper_32_bits (int) ; 

void si_ring_ib_execute(struct radeon_device *rdev, struct radeon_ib *ib)
{
	struct radeon_ring *ring = &rdev->ring[ib->ring];
	unsigned vm_id = ib->vm ? ib->vm->ids[ib->ring].id : 0;
	u32 header;

	if (ib->is_const_ib) {
		/* set switch buffer packet before const IB */
		radeon_ring_write(ring, PACKET3(PACKET3_SWITCH_BUFFER, 0));
		radeon_ring_write(ring, 0);

		header = PACKET3(PACKET3_INDIRECT_BUFFER_CONST, 2);
	} else {
		u32 next_rptr;
		if (ring->rptr_save_reg) {
			next_rptr = ring->wptr + 3 + 4 + 8;
			radeon_ring_write(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
			radeon_ring_write(ring, ((ring->rptr_save_reg -
						  PACKET3_SET_CONFIG_REG_START) >> 2));
			radeon_ring_write(ring, next_rptr);
		} else if (rdev->wb.enabled) {
			next_rptr = ring->wptr + 5 + 4 + 8;
			radeon_ring_write(ring, PACKET3(PACKET3_WRITE_DATA, 3));
			radeon_ring_write(ring, (1 << 8));
			radeon_ring_write(ring, ring->next_rptr_gpu_addr & 0xfffffffc);
			radeon_ring_write(ring, upper_32_bits(ring->next_rptr_gpu_addr));
			radeon_ring_write(ring, next_rptr);
		}

		header = PACKET3(PACKET3_INDIRECT_BUFFER, 2);
	}

	radeon_ring_write(ring, header);
	radeon_ring_write(ring,
#ifdef __BIG_ENDIAN
			  (2 << 0) |
#endif
			  (ib->gpu_addr & 0xFFFFFFFC));
	radeon_ring_write(ring, upper_32_bits(ib->gpu_addr) & 0xFFFF);
	radeon_ring_write(ring, ib->length_dw | (vm_id << 24));

	if (!ib->is_const_ib) {
		/* flush read cache over gart for this vmid */
		radeon_ring_write(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
		radeon_ring_write(ring, (CP_COHER_CNTL2 - PACKET3_SET_CONFIG_REG_START) >> 2);
		radeon_ring_write(ring, vm_id);
		radeon_ring_write(ring, PACKET3(PACKET3_SURFACE_SYNC, 3));
		radeon_ring_write(ring, PACKET3_TCL1_ACTION_ENA |
				  PACKET3_TC_ACTION_ENA |
				  PACKET3_SH_KCACHE_ACTION_ENA |
				  PACKET3_SH_ICACHE_ACTION_ENA);
		radeon_ring_write(ring, 0xFFFFFFFF);
		radeon_ring_write(ring, 0);
		radeon_ring_write(ring, 10); /* poll interval */
	}
}
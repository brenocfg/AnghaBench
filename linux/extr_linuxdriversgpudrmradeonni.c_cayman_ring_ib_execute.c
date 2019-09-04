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
typedef  unsigned int uint32_t ;
typedef  unsigned int u32 ;
struct radeon_ring {int rptr_save_reg; unsigned int wptr; } ;
struct radeon_ib {size_t ring; int gpu_addr; unsigned int length_dw; TYPE_2__* vm; } ;
struct radeon_device {struct radeon_ring* ring; } ;
struct TYPE_4__ {TYPE_1__* ids; } ;
struct TYPE_3__ {unsigned int id; } ;

/* Variables and functions */
 unsigned int PACKET3 (int /*<<< orphan*/ ,int) ; 
 unsigned int PACKET3_ENGINE_ME ; 
 unsigned int PACKET3_FULL_CACHE_ENA ; 
 int /*<<< orphan*/  PACKET3_INDIRECT_BUFFER ; 
 int /*<<< orphan*/  PACKET3_MODE_CONTROL ; 
 int /*<<< orphan*/  PACKET3_SET_CONFIG_REG ; 
 int PACKET3_SET_CONFIG_REG_START ; 
 unsigned int PACKET3_SH_ACTION_ENA ; 
 int /*<<< orphan*/  PACKET3_SURFACE_SYNC ; 
 unsigned int PACKET3_TC_ACTION_ENA ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,unsigned int) ; 
 int upper_32_bits (int) ; 

void cayman_ring_ib_execute(struct radeon_device *rdev, struct radeon_ib *ib)
{
	struct radeon_ring *ring = &rdev->ring[ib->ring];
	unsigned vm_id = ib->vm ? ib->vm->ids[ib->ring].id : 0;
	u32 cp_coher_cntl = PACKET3_FULL_CACHE_ENA | PACKET3_TC_ACTION_ENA |
		PACKET3_SH_ACTION_ENA;

	/* set to DX10/11 mode */
	radeon_ring_write(ring, PACKET3(PACKET3_MODE_CONTROL, 0));
	radeon_ring_write(ring, 1);

	if (ring->rptr_save_reg) {
		uint32_t next_rptr = ring->wptr + 3 + 4 + 8;
		radeon_ring_write(ring, PACKET3(PACKET3_SET_CONFIG_REG, 1));
		radeon_ring_write(ring, ((ring->rptr_save_reg - 
					  PACKET3_SET_CONFIG_REG_START) >> 2));
		radeon_ring_write(ring, next_rptr);
	}

	radeon_ring_write(ring, PACKET3(PACKET3_INDIRECT_BUFFER, 2));
	radeon_ring_write(ring,
#ifdef __BIG_ENDIAN
			  (2 << 0) |
#endif
			  (ib->gpu_addr & 0xFFFFFFFC));
	radeon_ring_write(ring, upper_32_bits(ib->gpu_addr) & 0xFF);
	radeon_ring_write(ring, ib->length_dw | (vm_id << 24));

	/* flush read cache over gart for this vmid */
	radeon_ring_write(ring, PACKET3(PACKET3_SURFACE_SYNC, 3));
	radeon_ring_write(ring, PACKET3_ENGINE_ME | cp_coher_cntl);
	radeon_ring_write(ring, 0xFFFFFFFF);
	radeon_ring_write(ring, 0);
	radeon_ring_write(ring, (vm_id << 24) | 10); /* poll interval */
}
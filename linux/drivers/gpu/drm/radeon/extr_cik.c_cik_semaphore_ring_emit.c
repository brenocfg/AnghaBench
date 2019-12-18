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
typedef  int /*<<< orphan*/  uint64_t ;
struct radeon_semaphore {int /*<<< orphan*/  gpu_addr; } ;
struct radeon_ring {scalar_t__ idx; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_MEM_SEMAPHORE ; 
 int /*<<< orphan*/  PACKET3_PFP_SYNC_ME ; 
 unsigned int PACKET3_SEM_SEL_SIGNAL ; 
 unsigned int PACKET3_SEM_SEL_WAIT ; 
 scalar_t__ RADEON_RING_TYPE_GFX_INDEX ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

bool cik_semaphore_ring_emit(struct radeon_device *rdev,
			     struct radeon_ring *ring,
			     struct radeon_semaphore *semaphore,
			     bool emit_wait)
{
	uint64_t addr = semaphore->gpu_addr;
	unsigned sel = emit_wait ? PACKET3_SEM_SEL_WAIT : PACKET3_SEM_SEL_SIGNAL;

	radeon_ring_write(ring, PACKET3(PACKET3_MEM_SEMAPHORE, 1));
	radeon_ring_write(ring, lower_32_bits(addr));
	radeon_ring_write(ring, (upper_32_bits(addr) & 0xffff) | sel);

	if (emit_wait && ring->idx == RADEON_RING_TYPE_GFX_INDEX) {
		/* Prevent the PFP from running ahead of the semaphore wait */
		radeon_ring_write(ring, PACKET3(PACKET3_PFP_SYNC_ME, 0));
		radeon_ring_write(ring, 0x0);
	}

	return true;
}
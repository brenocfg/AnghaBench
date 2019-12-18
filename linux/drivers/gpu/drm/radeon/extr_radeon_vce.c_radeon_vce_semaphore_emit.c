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
struct radeon_semaphore {int gpu_addr; } ;
struct radeon_ring {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int VCE_CMD_END ; 
 int VCE_CMD_SEMAPHORE ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int /*<<< orphan*/ ) ; 

bool radeon_vce_semaphore_emit(struct radeon_device *rdev,
			       struct radeon_ring *ring,
			       struct radeon_semaphore *semaphore,
			       bool emit_wait)
{
	uint64_t addr = semaphore->gpu_addr;

	radeon_ring_write(ring, cpu_to_le32(VCE_CMD_SEMAPHORE));
	radeon_ring_write(ring, cpu_to_le32((addr >> 3) & 0x000FFFFF));
	radeon_ring_write(ring, cpu_to_le32((addr >> 23) & 0x000FFFFF));
	radeon_ring_write(ring, cpu_to_le32(0x01003000 | (emit_wait ? 1 : 0)));
	if (!emit_wait)
		radeon_ring_write(ring, cpu_to_le32(VCE_CMD_END));

	return true;
}
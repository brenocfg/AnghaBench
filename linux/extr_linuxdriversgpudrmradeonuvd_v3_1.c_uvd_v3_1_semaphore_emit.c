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
 int PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD_SEMA_ADDR_HIGH ; 
 int /*<<< orphan*/  UVD_SEMA_ADDR_LOW ; 
 int /*<<< orphan*/  UVD_SEMA_CMD ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 

bool uvd_v3_1_semaphore_emit(struct radeon_device *rdev,
			     struct radeon_ring *ring,
			     struct radeon_semaphore *semaphore,
			     bool emit_wait)
{
	uint64_t addr = semaphore->gpu_addr;

	radeon_ring_write(ring, PACKET0(UVD_SEMA_ADDR_LOW, 0));
	radeon_ring_write(ring, (addr >> 3) & 0x000FFFFF);

	radeon_ring_write(ring, PACKET0(UVD_SEMA_ADDR_HIGH, 0));
	radeon_ring_write(ring, (addr >> 23) & 0x000FFFFF);

	radeon_ring_write(ring, PACKET0(UVD_SEMA_CMD, 0));
	radeon_ring_write(ring, 0x80 | (emit_wait ? 1 : 0));

	return true;
}
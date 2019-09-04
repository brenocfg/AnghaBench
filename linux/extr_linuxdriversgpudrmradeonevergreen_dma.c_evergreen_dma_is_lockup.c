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
typedef  int u32 ;
struct radeon_ring {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int RADEON_RESET_DMA ; 
 int evergreen_gpu_check_soft_reset (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_ring_lockup_update (struct radeon_device*,struct radeon_ring*) ; 
 int radeon_ring_test_lockup (struct radeon_device*,struct radeon_ring*) ; 

bool evergreen_dma_is_lockup(struct radeon_device *rdev, struct radeon_ring *ring)
{
	u32 reset_mask = evergreen_gpu_check_soft_reset(rdev);

	if (!(reset_mask & RADEON_RESET_DMA)) {
		radeon_ring_lockup_update(rdev, ring);
		return false;
	}
	return radeon_ring_test_lockup(rdev, ring);
}
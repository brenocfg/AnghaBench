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
struct radeon_ring {int wptr; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RB_WPTR ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

void r600_dma_set_wptr(struct radeon_device *rdev,
		       struct radeon_ring *ring)
{
	WREG32(DMA_RB_WPTR, (ring->wptr << 2) & 0x3fffc);
}
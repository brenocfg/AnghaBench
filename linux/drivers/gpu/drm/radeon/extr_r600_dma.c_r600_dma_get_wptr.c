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
typedef  int uint32_t ;
struct radeon_ring {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RB_WPTR ; 
 int RREG32 (int /*<<< orphan*/ ) ; 

uint32_t r600_dma_get_wptr(struct radeon_device *rdev,
			   struct radeon_ring *ring)
{
	return (RREG32(DMA_RB_WPTR) & 0x3fffc) >> 2;
}
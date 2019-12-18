#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u32 ;
struct radeon_ring {int rptr_offs; } ;
struct TYPE_2__ {int* wb; scalar_t__ enabled; } ;
struct radeon_device {TYPE_1__ wb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RB_RPTR ; 
 int RREG32 (int /*<<< orphan*/ ) ; 

uint32_t r600_dma_get_rptr(struct radeon_device *rdev,
			   struct radeon_ring *ring)
{
	u32 rptr;

	if (rdev->wb.enabled)
		rptr = rdev->wb.wb[ring->rptr_offs/4];
	else
		rptr = RREG32(DMA_RB_RPTR);

	return (rptr & 0x3fffc) >> 2;
}
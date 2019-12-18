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
typedef  int /*<<< orphan*/  uint32_t ;
struct radeon_ring {scalar_t__ idx; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 scalar_t__ TN_RING_TYPE_VCE1_INDEX ; 
 int /*<<< orphan*/  VCE_RB_WPTR ; 
 int /*<<< orphan*/  VCE_RB_WPTR2 ; 

uint32_t vce_v1_0_get_wptr(struct radeon_device *rdev,
			   struct radeon_ring *ring)
{
	if (ring->idx == TN_RING_TYPE_VCE1_INDEX)
		return RREG32(VCE_RB_WPTR);
	else
		return RREG32(VCE_RB_WPTR2);
}
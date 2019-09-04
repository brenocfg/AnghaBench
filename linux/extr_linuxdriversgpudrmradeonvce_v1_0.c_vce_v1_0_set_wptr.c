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
struct radeon_ring {scalar_t__ idx; int /*<<< orphan*/  wptr; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TN_RING_TYPE_VCE1_INDEX ; 
 int /*<<< orphan*/  VCE_RB_WPTR ; 
 int /*<<< orphan*/  VCE_RB_WPTR2 ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vce_v1_0_set_wptr(struct radeon_device *rdev,
		       struct radeon_ring *ring)
{
	if (ring->idx == TN_RING_TYPE_VCE1_INDEX)
		WREG32(VCE_RB_WPTR, ring->wptr);
	else
		WREG32(VCE_RB_WPTR2, ring->wptr);
}
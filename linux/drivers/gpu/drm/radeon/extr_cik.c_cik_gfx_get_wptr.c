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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_ring {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_RB0_WPTR ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 

u32 cik_gfx_get_wptr(struct radeon_device *rdev,
		     struct radeon_ring *ring)
{
	return RREG32(CP_RB0_WPTR);
}
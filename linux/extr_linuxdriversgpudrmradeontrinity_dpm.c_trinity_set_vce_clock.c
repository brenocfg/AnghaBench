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
struct radeon_ps {scalar_t__ evclk; scalar_t__ ecclk; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  radeon_set_vce_clocks (struct radeon_device*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vce_v1_0_enable_mgcg (struct radeon_device*,int) ; 

__attribute__((used)) static void trinity_set_vce_clock(struct radeon_device *rdev,
				  struct radeon_ps *new_rps,
				  struct radeon_ps *old_rps)
{
	if ((old_rps->evclk != new_rps->evclk) ||
	    (old_rps->ecclk != new_rps->ecclk)) {
		/* turn the clocks on when encoding, off otherwise */
		if (new_rps->evclk || new_rps->ecclk)
			vce_v1_0_enable_mgcg(rdev, false);
		else
			vce_v1_0_enable_mgcg(rdev, true);
		radeon_set_vce_clocks(rdev, new_rps->evclk, new_rps->ecclk);
	}
}
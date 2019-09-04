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
struct radeon_ps {scalar_t__ vclk; scalar_t__ dclk; } ;
struct radeon_device {int dummy; } ;
struct ni_ps {int performance_level_count; TYPE_1__* performance_levels; } ;
struct TYPE_2__ {scalar_t__ sclk; } ;

/* Variables and functions */
 struct ni_ps* ni_get_ps (struct radeon_ps*) ; 
 int /*<<< orphan*/  radeon_set_uvd_clocks (struct radeon_device*,scalar_t__,scalar_t__) ; 

void ni_set_uvd_clock_before_set_eng_clock(struct radeon_device *rdev,
					   struct radeon_ps *new_ps,
					   struct radeon_ps *old_ps)
{
	struct ni_ps *new_state = ni_get_ps(new_ps);
	struct ni_ps *current_state = ni_get_ps(old_ps);

	if ((new_ps->vclk == old_ps->vclk) &&
	    (new_ps->dclk == old_ps->dclk))
		return;

	if (new_state->performance_levels[new_state->performance_level_count - 1].sclk >=
	    current_state->performance_levels[current_state->performance_level_count - 1].sclk)
		return;

	radeon_set_uvd_clocks(rdev, new_ps->vclk, new_ps->dclk);
}
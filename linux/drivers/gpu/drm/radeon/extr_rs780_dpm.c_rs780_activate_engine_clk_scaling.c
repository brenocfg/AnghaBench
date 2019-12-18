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
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;
struct igp_ps {scalar_t__ sclk_high; scalar_t__ sclk_low; } ;

/* Variables and functions */
 int /*<<< orphan*/  rs780_clk_scaling_enable (struct radeon_device*,int) ; 
 struct igp_ps* rs780_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static void rs780_activate_engine_clk_scaling(struct radeon_device *rdev,
					      struct radeon_ps *new_ps,
					      struct radeon_ps *old_ps)
{
	struct igp_ps *new_state = rs780_get_ps(new_ps);
	struct igp_ps *old_state = rs780_get_ps(old_ps);

	if ((new_state->sclk_high == old_state->sclk_high) &&
	    (new_state->sclk_low == old_state->sclk_low))
		return;

	if (new_state->sclk_high == new_state->sclk_low)
		return;

	rs780_clk_scaling_enable(rdev, true);
}
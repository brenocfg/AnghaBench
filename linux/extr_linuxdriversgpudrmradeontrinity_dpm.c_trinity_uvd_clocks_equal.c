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
struct trinity_ps {scalar_t__ vclk_low_divider; scalar_t__ vclk_high_divider; scalar_t__ dclk_low_divider; scalar_t__ dclk_high_divider; } ;
struct radeon_ps {scalar_t__ vclk; scalar_t__ dclk; } ;

/* Variables and functions */
 struct trinity_ps* trinity_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static bool trinity_uvd_clocks_equal(struct radeon_ps *rps1,
				     struct radeon_ps *rps2)
{
	struct trinity_ps *ps1 = trinity_get_ps(rps1);
	struct trinity_ps *ps2 = trinity_get_ps(rps2);

	if ((rps1->vclk == rps2->vclk) &&
	    (rps1->dclk == rps2->dclk) &&
	    (ps1->vclk_low_divider == ps2->vclk_low_divider) &&
	    (ps1->vclk_high_divider == ps2->vclk_high_divider) &&
	    (ps1->dclk_low_divider == ps2->dclk_low_divider) &&
	    (ps1->dclk_high_divider == ps2->dclk_high_divider))
		return true;
	else
		return false;
}
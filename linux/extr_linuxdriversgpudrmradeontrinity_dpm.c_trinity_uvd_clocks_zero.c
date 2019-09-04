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
struct radeon_ps {scalar_t__ vclk; scalar_t__ dclk; } ;

/* Variables and functions */

__attribute__((used)) static bool trinity_uvd_clocks_zero(struct radeon_ps *rps)
{
	if ((rps->vclk == 0) && (rps->dclk == 0))
		return true;
	else
		return false;
}
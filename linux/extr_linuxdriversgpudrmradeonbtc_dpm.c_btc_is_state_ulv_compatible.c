#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ mclk; scalar_t__ vddci; } ;
struct rv7xx_ps {TYPE_2__ low; } ;
struct rv7xx_pl {scalar_t__ mclk; scalar_t__ vddci; } ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;
struct TYPE_3__ {struct rv7xx_pl* pl; } ;
struct evergreen_power_info {TYPE_1__ ulv; } ;

/* Variables and functions */
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 struct rv7xx_ps* rv770_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static bool btc_is_state_ulv_compatible(struct radeon_device *rdev,
					struct radeon_ps *radeon_state)
{
	struct rv7xx_ps *state = rv770_get_ps(radeon_state);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct rv7xx_pl *ulv_pl = eg_pi->ulv.pl;

	if (state->low.mclk != ulv_pl->mclk)
		return false;

	if (state->low.vddci != ulv_pl->vddci)
		return false;

	/* XXX check minclocks, etc. */

	return true;
}
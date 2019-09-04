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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  sclk; } ;
struct TYPE_3__ {int /*<<< orphan*/  sclk; } ;
struct rv7xx_ps {TYPE_2__ high; TYPE_1__ low; } ;
struct radeon_device {int dummy; } ;
struct evergreen_power_info {int /*<<< orphan*/  requested_rps; } ;

/* Variables and functions */
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 struct rv7xx_ps* rv770_get_ps (int /*<<< orphan*/ *) ; 

u32 btc_dpm_get_sclk(struct radeon_device *rdev, bool low)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct rv7xx_ps *requested_state = rv770_get_ps(&eg_pi->requested_rps);

	if (low)
		return requested_state->low.sclk;
	else
		return requested_state->high.sclk;
}
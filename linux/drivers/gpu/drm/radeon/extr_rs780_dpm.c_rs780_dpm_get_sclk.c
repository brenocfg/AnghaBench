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
struct TYPE_3__ {int /*<<< orphan*/  requested_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;
struct igp_ps {int /*<<< orphan*/  sclk_high; int /*<<< orphan*/  sclk_low; } ;

/* Variables and functions */
 struct igp_ps* rs780_get_ps (int /*<<< orphan*/ ) ; 

u32 rs780_dpm_get_sclk(struct radeon_device *rdev, bool low)
{
	struct igp_ps *requested_state = rs780_get_ps(rdev->pm.dpm.requested_ps);

	if (low)
		return requested_state->sclk_low;
	else
		return requested_state->sclk_high;
}
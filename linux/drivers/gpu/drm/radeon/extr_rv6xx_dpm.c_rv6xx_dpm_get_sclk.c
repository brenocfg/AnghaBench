#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int /*<<< orphan*/  sclk; } ;
struct TYPE_7__ {int /*<<< orphan*/  sclk; } ;
struct rv6xx_ps {TYPE_4__ high; TYPE_3__ low; } ;
struct TYPE_5__ {int /*<<< orphan*/  requested_ps; } ;
struct TYPE_6__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;

/* Variables and functions */
 struct rv6xx_ps* rv6xx_get_ps (int /*<<< orphan*/ ) ; 

u32 rv6xx_dpm_get_sclk(struct radeon_device *rdev, bool low)
{
	struct rv6xx_ps *requested_state = rv6xx_get_ps(rdev->pm.dpm.requested_ps);

	if (low)
		return requested_state->low.sclk;
	else
		return requested_state->high.sclk;
}
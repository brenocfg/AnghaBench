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
struct TYPE_3__ {scalar_t__ pm_method; scalar_t__ dpm_enabled; } ;
struct TYPE_4__ {int /*<<< orphan*/  idle_work; } ;
struct radeon_device {TYPE_1__ pm; TYPE_2__ vce; } ;

/* Variables and functions */
 scalar_t__ PM_METHOD_DPM ; 
 int /*<<< orphan*/  VCE_IDLE_TIMEOUT_MS ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_dpm_enable_vce (struct radeon_device*,int) ; 
 int /*<<< orphan*/  radeon_set_vce_clocks (struct radeon_device*,int,int) ; 
 int schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void radeon_vce_note_usage(struct radeon_device *rdev)
{
	bool streams_changed = false;
	bool set_clocks = !cancel_delayed_work_sync(&rdev->vce.idle_work);
	set_clocks &= schedule_delayed_work(&rdev->vce.idle_work,
					    msecs_to_jiffies(VCE_IDLE_TIMEOUT_MS));

	if ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled) {
		/* XXX figure out if the streams changed */
		streams_changed = false;
	}

	if (set_clocks || streams_changed) {
		if ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled) {
			radeon_dpm_enable_vce(rdev, true);
		} else {
			radeon_set_vce_clocks(rdev, 53300, 40000);
		}
	}
}
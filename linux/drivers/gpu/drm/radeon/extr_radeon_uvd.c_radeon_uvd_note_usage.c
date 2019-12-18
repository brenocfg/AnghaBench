#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int sd; unsigned int hd; } ;
struct TYPE_6__ {scalar_t__ pm_method; scalar_t__ dpm_enabled; TYPE_2__ dpm; } ;
struct TYPE_4__ {int /*<<< orphan*/  idle_work; } ;
struct radeon_device {TYPE_3__ pm; TYPE_1__ uvd; } ;

/* Variables and functions */
 scalar_t__ PM_METHOD_DPM ; 
 int /*<<< orphan*/  UVD_IDLE_TIMEOUT_MS ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_dpm_enable_uvd (struct radeon_device*,int) ; 
 int /*<<< orphan*/  radeon_set_uvd_clocks (struct radeon_device*,int,int) ; 
 int /*<<< orphan*/  radeon_uvd_count_handles (struct radeon_device*,unsigned int*,unsigned int*) ; 
 int schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void radeon_uvd_note_usage(struct radeon_device *rdev)
{
	bool streams_changed = false;
	bool set_clocks = !cancel_delayed_work_sync(&rdev->uvd.idle_work);
	set_clocks &= schedule_delayed_work(&rdev->uvd.idle_work,
					    msecs_to_jiffies(UVD_IDLE_TIMEOUT_MS));

	if ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled) {
		unsigned hd = 0, sd = 0;
		radeon_uvd_count_handles(rdev, &sd, &hd);
		if ((rdev->pm.dpm.sd != sd) ||
		    (rdev->pm.dpm.hd != hd)) {
			rdev->pm.dpm.sd = sd;
			rdev->pm.dpm.hd = hd;
			/* disable this for now */
			/*streams_changed = true;*/
		}
	}

	if (set_clocks || streams_changed) {
		if ((rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled) {
			radeon_dpm_enable_uvd(rdev, true);
		} else {
			radeon_set_uvd_clocks(rdev, 53300, 40000);
		}
	}
}
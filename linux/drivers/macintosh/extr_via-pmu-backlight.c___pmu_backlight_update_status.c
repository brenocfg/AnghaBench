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
struct TYPE_2__ {int brightness; scalar_t__ power; scalar_t__ fb_blank; } ;
struct backlight_device {TYPE_1__ props; } ;
struct adb_request {int dummy; } ;

/* Variables and functions */
 scalar_t__ FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  PMU_BACKLIGHT_BRIGHT ; 
 int /*<<< orphan*/  PMU_POWER_CTRL ; 
 int PMU_POW_BACKLIGHT ; 
 int PMU_POW_OFF ; 
 int PMU_POW_ON ; 
 int pmu_backlight_get_level_brightness (int) ; 
 int /*<<< orphan*/  pmu_request (struct adb_request*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmu_wait_complete (struct adb_request*) ; 

__attribute__((used)) static int __pmu_backlight_update_status(struct backlight_device *bd)
{
	struct adb_request req;
	int level = bd->props.brightness;


	if (bd->props.power != FB_BLANK_UNBLANK ||
	    bd->props.fb_blank != FB_BLANK_UNBLANK)
		level = 0;

	if (level > 0) {
		int pmulevel = pmu_backlight_get_level_brightness(level);

		pmu_request(&req, NULL, 2, PMU_BACKLIGHT_BRIGHT, pmulevel);
		pmu_wait_complete(&req);

		pmu_request(&req, NULL, 2, PMU_POWER_CTRL,
			PMU_POW_BACKLIGHT | PMU_POW_ON);
		pmu_wait_complete(&req);
	} else {
		pmu_request(&req, NULL, 2, PMU_POWER_CTRL,
			PMU_POW_BACKLIGHT | PMU_POW_OFF);
		pmu_wait_complete(&req);
	}

	return 0;
}
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

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernel_backlight_disabled ; 
 int pmac_backlight_set_legacy_queued ; 
 int /*<<< orphan*/  pmac_backlight_set_legacy_work ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void pmac_backlight_set_legacy_brightness_pmu(int brightness) {
	if (atomic_read(&kernel_backlight_disabled))
		return;

	pmac_backlight_set_legacy_queued = brightness;
	schedule_work(&pmac_backlight_set_legacy_work);
}
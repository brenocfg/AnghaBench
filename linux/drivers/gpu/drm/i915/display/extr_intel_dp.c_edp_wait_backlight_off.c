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
struct intel_dp {int /*<<< orphan*/  backlight_off_delay; int /*<<< orphan*/  last_backlight_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  wait_remaining_ms_from_jiffies (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void edp_wait_backlight_off(struct intel_dp *intel_dp)
{
	wait_remaining_ms_from_jiffies(intel_dp->last_backlight_off,
				       intel_dp->backlight_off_delay);
}
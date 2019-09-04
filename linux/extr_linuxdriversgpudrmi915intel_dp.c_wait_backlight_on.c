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
struct intel_dp {int /*<<< orphan*/  backlight_on_delay; int /*<<< orphan*/  last_power_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  wait_remaining_ms_from_jiffies (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wait_backlight_on(struct intel_dp *intel_dp)
{
	wait_remaining_ms_from_jiffies(intel_dp->last_power_on,
				       intel_dp->backlight_on_delay);
}
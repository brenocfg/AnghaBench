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
 int /*<<< orphan*/  GEF_WDC_ENABLED_TRUE ; 
 int /*<<< orphan*/  GEF_WDC_ENABLE_SHIFT ; 
 scalar_t__ gef_wdt_toggle_wdc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 

__attribute__((used)) static void gef_wdt_handler_disable(void)
{
	if (gef_wdt_toggle_wdc(GEF_WDC_ENABLED_TRUE,
				   GEF_WDC_ENABLE_SHIFT))
		pr_notice("watchdog deactivated\n");
}
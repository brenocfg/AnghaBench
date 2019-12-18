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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * pm_power_off ; 
 int /*<<< orphan*/ * syscon_poweroff ; 

__attribute__((used)) static int syscon_poweroff_remove(struct platform_device *pdev)
{
	if (pm_power_off == syscon_poweroff)
		pm_power_off = NULL;

	return 0;
}
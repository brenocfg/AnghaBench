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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ab8500_power_off ; 
 scalar_t__ pm_power_off ; 
 int /*<<< orphan*/ * sysctrl_dev ; 

__attribute__((used)) static int ab8500_sysctrl_probe(struct platform_device *pdev)
{
	sysctrl_dev = &pdev->dev;

	if (!pm_power_off)
		pm_power_off = ab8500_power_off;

	return 0;
}
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
struct thermal_cooling_device {struct clock_cooling_device* devdata; } ;
struct clock_cooling_device {int /*<<< orphan*/  id; int /*<<< orphan*/  cdev; int /*<<< orphan*/  freq_table; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk_rate_change_nb; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_notifier_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock_ida ; 
 int /*<<< orphan*/  dev_pm_opp_free_cpufreq_table (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_cooling_device_unregister (int /*<<< orphan*/ ) ; 

void clock_cooling_unregister(struct thermal_cooling_device *cdev)
{
	struct clock_cooling_device *ccdev;

	if (!cdev)
		return;

	ccdev = cdev->devdata;

	clk_notifier_unregister(ccdev->clk, &ccdev->clk_rate_change_nb);
	dev_pm_opp_free_cpufreq_table(ccdev->dev, &ccdev->freq_table);

	thermal_cooling_device_unregister(ccdev->cdev);
	ida_simple_remove(&clock_ida, ccdev->id);
}
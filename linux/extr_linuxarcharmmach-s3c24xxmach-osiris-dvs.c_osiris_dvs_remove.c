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
 int /*<<< orphan*/  CPUFREQ_TRANSITION_NOTIFIER ; 
 int /*<<< orphan*/  OSIRIS_GPIO_DVS ; 
 int /*<<< orphan*/  cpufreq_unregister_notifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  osiris_dvs_nb ; 
 int /*<<< orphan*/  osiris_dvs_tps_setdvs (int) ; 

__attribute__((used)) static int osiris_dvs_remove(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "exiting\n");

	/* disable any current dvs */
	gpio_set_value(OSIRIS_GPIO_DVS, 1);
	osiris_dvs_tps_setdvs(false);

	cpufreq_unregister_notifier(&osiris_dvs_nb,
				    CPUFREQ_TRANSITION_NOTIFIER);

	gpio_free(OSIRIS_GPIO_DVS);

	return 0;
}
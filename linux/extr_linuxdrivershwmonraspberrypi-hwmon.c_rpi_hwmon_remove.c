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
struct rpi_hwmon_data {int /*<<< orphan*/  get_values_poll_work; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct rpi_hwmon_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int rpi_hwmon_remove(struct platform_device *pdev)
{
	struct rpi_hwmon_data *data = platform_get_drvdata(pdev);

	cancel_delayed_work_sync(&data->get_values_poll_work);

	return 0;
}
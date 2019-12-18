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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;
struct f71805f_data {int /*<<< orphan*/  hwmon_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  f71805f_group ; 
 int /*<<< orphan*/ * f71805f_group_optin ; 
 int /*<<< orphan*/  f71805f_group_pwm_freq ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 struct f71805f_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int f71805f_remove(struct platform_device *pdev)
{
	struct f71805f_data *data = platform_get_drvdata(pdev);
	int i;

	hwmon_device_unregister(data->hwmon_dev);
	sysfs_remove_group(&pdev->dev.kobj, &f71805f_group);
	for (i = 0; i < 4; i++)
		sysfs_remove_group(&pdev->dev.kobj, &f71805f_group_optin[i]);
	sysfs_remove_group(&pdev->dev.kobj, &f71805f_group_pwm_freq);

	return 0;
}
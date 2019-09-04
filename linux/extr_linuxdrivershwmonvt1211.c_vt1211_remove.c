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
struct vt1211_data {int /*<<< orphan*/  hwmon_dev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 struct vt1211_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  vt1211_remove_sysfs (struct platform_device*) ; 

__attribute__((used)) static int vt1211_remove(struct platform_device *pdev)
{
	struct vt1211_data *data = platform_get_drvdata(pdev);

	hwmon_device_unregister(data->hwmon_dev);
	vt1211_remove_sysfs(pdev);

	return 0;
}
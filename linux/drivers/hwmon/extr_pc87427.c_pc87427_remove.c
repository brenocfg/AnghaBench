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
struct pc87427_data {int /*<<< orphan*/  hwmon_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pc87427_remove_files (int /*<<< orphan*/ *) ; 
 struct pc87427_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int pc87427_remove(struct platform_device *pdev)
{
	struct pc87427_data *data = platform_get_drvdata(pdev);

	hwmon_device_unregister(data->hwmon_dev);
	pc87427_remove_files(&pdev->dev);

	return 0;
}
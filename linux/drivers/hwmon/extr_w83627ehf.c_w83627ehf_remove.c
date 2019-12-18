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
struct w83627ehf_data {int /*<<< orphan*/  addr; int /*<<< orphan*/  hwmon_dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOREGION_LENGTH ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 struct w83627ehf_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83627ehf_device_remove_files (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int w83627ehf_remove(struct platform_device *pdev)
{
	struct w83627ehf_data *data = platform_get_drvdata(pdev);

	hwmon_device_unregister(data->hwmon_dev);
	w83627ehf_device_remove_files(&pdev->dev);
	release_region(data->addr, IOREGION_LENGTH);

	return 0;
}
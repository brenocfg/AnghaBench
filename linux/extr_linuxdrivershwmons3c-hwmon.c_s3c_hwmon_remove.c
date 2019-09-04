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
struct s3c_hwmon {int /*<<< orphan*/  client; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/ * attrs; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 struct s3c_hwmon* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  s3c_adc_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_hwmon_remove_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s3c_hwmon_remove_raw (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s3c_hwmon_remove(struct platform_device *dev)
{
	struct s3c_hwmon *hwmon = platform_get_drvdata(dev);
	int i;

	s3c_hwmon_remove_raw(&dev->dev);

	for (i = 0; i < ARRAY_SIZE(hwmon->attrs); i++)
		s3c_hwmon_remove_attr(&dev->dev, &hwmon->attrs[i]);

	hwmon_device_unregister(hwmon->hwmon_dev);
	s3c_adc_release(hwmon->client);

	return 0;
}
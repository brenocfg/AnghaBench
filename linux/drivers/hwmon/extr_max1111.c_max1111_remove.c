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
struct spi_device {TYPE_1__ dev; } ;
struct max1111_data {int /*<<< orphan*/  drvdata_lock; int /*<<< orphan*/  hwmon_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max1110_attr_group ; 
 int /*<<< orphan*/  max1111_attr_group ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct max1111_data* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * the_max1111 ; 

__attribute__((used)) static int max1111_remove(struct spi_device *spi)
{
	struct max1111_data *data = spi_get_drvdata(spi);

#ifdef CONFIG_SHARPSL_PM
	the_max1111 = NULL;
#endif
	hwmon_device_unregister(data->hwmon_dev);
	sysfs_remove_group(&spi->dev.kobj, &max1110_attr_group);
	sysfs_remove_group(&spi->dev.kobj, &max1111_attr_group);
	mutex_destroy(&data->drvdata_lock);
	return 0;
}
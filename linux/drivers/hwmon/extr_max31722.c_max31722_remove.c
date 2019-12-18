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
struct spi_device {int dummy; } ;
struct max31722_data {int /*<<< orphan*/  hwmon_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX31722_MODE_STANDBY ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int max31722_set_mode (struct max31722_data*,int /*<<< orphan*/ ) ; 
 struct max31722_data* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int max31722_remove(struct spi_device *spi)
{
	struct max31722_data *data = spi_get_drvdata(spi);

	hwmon_device_unregister(data->hwmon_dev);

	return max31722_set_mode(data, MAX31722_MODE_STANDBY);
}
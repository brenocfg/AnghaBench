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
struct spi_device {int /*<<< orphan*/  modalias; int /*<<< orphan*/  dev; } ;
struct max31722_data {int mode; int /*<<< orphan*/  hwmon_dev; struct spi_device* spi_device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX31722_MODE_CONTINUOUS ; 
 int MAX31722_MODE_STANDBY ; 
 int MAX31722_RESOLUTION_12BIT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct max31722_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register_with_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct max31722_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max31722_groups ; 
 int max31722_set_mode (struct max31722_data*,int) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct max31722_data*) ; 

__attribute__((used)) static int max31722_probe(struct spi_device *spi)
{
	int ret;
	struct max31722_data *data;

	data = devm_kzalloc(&spi->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	spi_set_drvdata(spi, data);
	data->spi_device = spi;
	/*
	 * Set SD bit to 0 so we can have continuous measurements.
	 * Set resolution to 12 bits for maximum precision.
	 */
	data->mode = MAX31722_MODE_CONTINUOUS | MAX31722_RESOLUTION_12BIT;
	ret = max31722_set_mode(data, MAX31722_MODE_CONTINUOUS);
	if (ret < 0)
		return ret;

	data->hwmon_dev = hwmon_device_register_with_groups(&spi->dev,
							    spi->modalias,
							    data,
							    max31722_groups);
	if (IS_ERR(data->hwmon_dev)) {
		max31722_set_mode(data, MAX31722_MODE_STANDBY);
		return PTR_ERR(data->hwmon_dev);
	}

	return 0;
}
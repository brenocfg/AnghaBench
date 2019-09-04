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
struct device {int dummy; } ;
struct ad7314_data {struct spi_device* spi_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  ad7314_groups ; 
 struct device* devm_hwmon_device_register_with_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ad7314_data*,int /*<<< orphan*/ ) ; 
 struct ad7314_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7314_probe(struct spi_device *spi_dev)
{
	struct ad7314_data *chip;
	struct device *hwmon_dev;

	chip = devm_kzalloc(&spi_dev->dev, sizeof(*chip), GFP_KERNEL);
	if (chip == NULL)
		return -ENOMEM;

	chip->spi_dev = spi_dev;
	hwmon_dev = devm_hwmon_device_register_with_groups(&spi_dev->dev,
							   spi_dev->modalias,
							   chip, ad7314_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}
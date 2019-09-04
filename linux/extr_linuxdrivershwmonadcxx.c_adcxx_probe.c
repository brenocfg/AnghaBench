#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spi_device {int /*<<< orphan*/  dev; } ;
struct adcxx {int reference; int channels; int /*<<< orphan*/  lock; int /*<<< orphan*/  hwmon_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_3__ {int driver_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 TYPE_2__* ad_input ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct adcxx* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct adcxx*) ; 

__attribute__((used)) static int adcxx_probe(struct spi_device *spi)
{
	int channels = spi_get_device_id(spi)->driver_data;
	struct adcxx *adc;
	int status;
	int i;

	adc = devm_kzalloc(&spi->dev, sizeof(*adc), GFP_KERNEL);
	if (!adc)
		return -ENOMEM;

	/* set a default value for the reference */
	adc->reference = 3300;
	adc->channels = channels;
	mutex_init(&adc->lock);

	mutex_lock(&adc->lock);

	spi_set_drvdata(spi, adc);

	for (i = 0; i < 3 + adc->channels; i++) {
		status = device_create_file(&spi->dev, &ad_input[i].dev_attr);
		if (status) {
			dev_err(&spi->dev, "device_create_file failed.\n");
			goto out_err;
		}
	}

	adc->hwmon_dev = hwmon_device_register(&spi->dev);
	if (IS_ERR(adc->hwmon_dev)) {
		dev_err(&spi->dev, "hwmon_device_register failed.\n");
		status = PTR_ERR(adc->hwmon_dev);
		goto out_err;
	}

	mutex_unlock(&adc->lock);
	return 0;

out_err:
	for (i--; i >= 0; i--)
		device_remove_file(&spi->dev, &ad_input[i].dev_attr);

	mutex_unlock(&adc->lock);
	return status;
}
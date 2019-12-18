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
typedef  int u8 ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct bmi160_data {int /*<<< orphan*/  regmap; } ;
typedef  enum bmi160_int_pin { ____Placeholder_bmi160_int_pin } bmi160_int_pin ;

/* Variables and functions */
 int BMI160_ACTIVE_HIGH ; 
 int BMI160_EDGE_TRIGGERED ; 
 int /*<<< orphan*/  BMI160_NORMAL_WRITE_USLEEP ; 
 int EINVAL ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_HIGH ; 
 int IRQF_TRIGGER_LOW ; 
 int IRQF_TRIGGER_RISING ; 
 int bmi160_config_pin (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct bmi160_data* iio_priv (struct iio_dev*) ; 
 int of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bmi160_config_device_irq(struct iio_dev *indio_dev, int irq_type,
				    enum bmi160_int_pin pin)
{
	bool open_drain;
	u8 irq_mask;
	struct bmi160_data *data = iio_priv(indio_dev);
	struct device *dev = regmap_get_device(data->regmap);

	/* Level-triggered, active-low is the default if we set all zeroes. */
	if (irq_type == IRQF_TRIGGER_RISING)
		irq_mask = BMI160_ACTIVE_HIGH | BMI160_EDGE_TRIGGERED;
	else if (irq_type == IRQF_TRIGGER_FALLING)
		irq_mask = BMI160_EDGE_TRIGGERED;
	else if (irq_type == IRQF_TRIGGER_HIGH)
		irq_mask = BMI160_ACTIVE_HIGH;
	else if (irq_type == IRQF_TRIGGER_LOW)
		irq_mask = 0;
	else {
		dev_err(&indio_dev->dev,
			"Invalid interrupt type 0x%x specified\n", irq_type);
		return -EINVAL;
	}

	open_drain = of_property_read_bool(dev->of_node, "drive-open-drain");

	return bmi160_config_pin(data->regmap, pin, open_drain, irq_mask,
				 BMI160_NORMAL_WRITE_USLEEP);
}
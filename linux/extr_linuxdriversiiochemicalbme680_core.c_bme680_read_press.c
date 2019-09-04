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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct bme680_data {int /*<<< orphan*/  regmap; } ;
typedef  int s32 ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int BME680_MEAS_SKIPPED ; 
 int /*<<< orphan*/  BME680_REG_PRESS_MSB ; 
 int EINVAL ; 
 int IIO_VAL_FRACTIONAL ; 
 int be32_to_cpu (scalar_t__) ; 
 int bme680_compensate_press (struct bme680_data*,int) ; 
 int bme680_read_temp (struct bme680_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bme680_read_press(struct bme680_data *data,
			     int *val, int *val2)
{
	struct device *dev = regmap_get_device(data->regmap);
	int ret;
	__be32 tmp = 0;
	s32 adc_press;

	/* Read and compensate temperature to get a reading of t_fine */
	ret = bme680_read_temp(data, NULL);
	if (ret < 0)
		return ret;

	ret = regmap_bulk_read(data->regmap, BME680_REG_PRESS_MSB,
			       (u8 *) &tmp, 3);
	if (ret < 0) {
		dev_err(dev, "failed to read pressure\n");
		return ret;
	}

	adc_press = be32_to_cpu(tmp) >> 12;
	if (adc_press == BME680_MEAS_SKIPPED) {
		/* reading was skipped */
		dev_err(dev, "reading pressure skipped\n");
		return -EINVAL;
	}

	*val = bme680_compensate_press(data, adc_press);
	*val2 = 100;
	return IIO_VAL_FRACTIONAL;
}
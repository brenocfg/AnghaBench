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
typedef  int u32 ;
struct device {int dummy; } ;
struct bme680_data {int /*<<< orphan*/  regmap; } ;
typedef  scalar_t__ s32 ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  BM6880_REG_HUMIDITY_MSB ; 
 scalar_t__ BME680_MEAS_SKIPPED ; 
 int EINVAL ; 
 int IIO_VAL_FRACTIONAL ; 
 scalar_t__ be16_to_cpu (scalar_t__) ; 
 int bme680_compensate_humid (struct bme680_data*,scalar_t__) ; 
 int bme680_read_temp (struct bme680_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bme680_read_humid(struct bme680_data *data,
			     int *val, int *val2)
{
	struct device *dev = regmap_get_device(data->regmap);
	int ret;
	__be16 tmp = 0;
	s32 adc_humidity;
	u32 comp_humidity;

	/* Read and compensate temperature to get a reading of t_fine */
	ret = bme680_read_temp(data, NULL);
	if (ret < 0)
		return ret;

	ret = regmap_bulk_read(data->regmap, BM6880_REG_HUMIDITY_MSB,
			       (u8 *) &tmp, 2);
	if (ret < 0) {
		dev_err(dev, "failed to read humidity\n");
		return ret;
	}

	adc_humidity = be16_to_cpu(tmp);
	if (adc_humidity == BME680_MEAS_SKIPPED) {
		/* reading was skipped */
		dev_err(dev, "reading humidity skipped\n");
		return -EINVAL;
	}
	comp_humidity = bme680_compensate_humid(data, adc_humidity);

	*val = comp_humidity;
	*val2 = 1000;
	return IIO_VAL_FRACTIONAL;
}
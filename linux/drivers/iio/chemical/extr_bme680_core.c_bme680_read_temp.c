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
typedef  int s16 ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int BME680_MEAS_SKIPPED ; 
 int /*<<< orphan*/  BME680_REG_TEMP_MSB ; 
 int EINVAL ; 
 int IIO_VAL_INT ; 
 int be32_to_cpu (scalar_t__) ; 
 int bme680_compensate_temp (struct bme680_data*,int) ; 
 int bme680_set_mode (struct bme680_data*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bme680_read_temp(struct bme680_data *data, int *val)
{
	struct device *dev = regmap_get_device(data->regmap);
	int ret;
	__be32 tmp = 0;
	s32 adc_temp;
	s16 comp_temp;

	/* set forced mode to trigger measurement */
	ret = bme680_set_mode(data, true);
	if (ret < 0)
		return ret;

	ret = regmap_bulk_read(data->regmap, BME680_REG_TEMP_MSB,
			       (u8 *) &tmp, 3);
	if (ret < 0) {
		dev_err(dev, "failed to read temperature\n");
		return ret;
	}

	adc_temp = be32_to_cpu(tmp) >> 12;
	if (adc_temp == BME680_MEAS_SKIPPED) {
		/* reading was skipped */
		dev_err(dev, "reading temperature skipped\n");
		return -EINVAL;
	}
	comp_temp = bme680_compensate_temp(data, adc_temp);
	/*
	 * val might be NULL if we're called by the read_press/read_humid
	 * routine which is callled to get t_fine value used in
	 * compensate_press/compensate_humid to get compensated
	 * pressure/humidity readings.
	 */
	if (val) {
		*val = comp_temp * 10; /* Centidegrees to millidegrees */
		return IIO_VAL_INT;
	}

	return ret;
}
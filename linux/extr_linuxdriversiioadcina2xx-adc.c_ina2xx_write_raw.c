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
struct ina2xx_chip_info {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  regmap; TYPE_1__* config; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  address; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip_id; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_HARDWAREGAIN 130 
#define  IIO_CHAN_INFO_INT_TIME 129 
#define  IIO_CHAN_INFO_OVERSAMPLING_RATIO 128 
 int /*<<< orphan*/  INA2XX_CONFIG ; 
 int /*<<< orphan*/  INA2XX_SHUNT_VOLTAGE ; 
 scalar_t__ iio_buffer_enabled (struct iio_dev*) ; 
 struct ina2xx_chip_info* iio_priv (struct iio_dev*) ; 
 int ina219_set_int_time_vbus (struct ina2xx_chip_info*,int,unsigned int*) ; 
 int ina219_set_int_time_vshunt (struct ina2xx_chip_info*,int,unsigned int*) ; 
 int ina219_set_vbus_range_denom (struct ina2xx_chip_info*,int,unsigned int*) ; 
 int ina219_set_vshunt_pga_gain (struct ina2xx_chip_info*,int,unsigned int*) ; 
 int /*<<< orphan*/  ina226 ; 
 int ina226_set_average (struct ina2xx_chip_info*,int,unsigned int*) ; 
 int ina226_set_int_time_vbus (struct ina2xx_chip_info*,int,unsigned int*) ; 
 int ina226_set_int_time_vshunt (struct ina2xx_chip_info*,int,unsigned int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ina2xx_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val, int val2, long mask)
{
	struct ina2xx_chip_info *chip = iio_priv(indio_dev);
	unsigned int config, tmp;
	int ret;

	if (iio_buffer_enabled(indio_dev))
		return -EBUSY;

	mutex_lock(&chip->state_lock);

	ret = regmap_read(chip->regmap, INA2XX_CONFIG, &config);
	if (ret)
		goto err;

	tmp = config;

	switch (mask) {
	case IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		ret = ina226_set_average(chip, val, &tmp);
		break;

	case IIO_CHAN_INFO_INT_TIME:
		if (chip->config->chip_id == ina226) {
			if (chan->address == INA2XX_SHUNT_VOLTAGE)
				ret = ina226_set_int_time_vshunt(chip, val2,
								 &tmp);
			else
				ret = ina226_set_int_time_vbus(chip, val2,
							       &tmp);
		} else {
			if (chan->address == INA2XX_SHUNT_VOLTAGE)
				ret = ina219_set_int_time_vshunt(chip, val2,
								 &tmp);
			else
				ret = ina219_set_int_time_vbus(chip, val2,
							       &tmp);
		}
		break;

	case IIO_CHAN_INFO_HARDWAREGAIN:
		if (chan->address == INA2XX_SHUNT_VOLTAGE)
			ret = ina219_set_vshunt_pga_gain(chip, val * 1000 +
							 val2 / 1000, &tmp);
		else
			ret = ina219_set_vbus_range_denom(chip, val, &tmp);
		break;

	default:
		ret = -EINVAL;
	}

	if (!ret && (tmp != config))
		ret = regmap_write(chip->regmap, INA2XX_CONFIG, tmp);
err:
	mutex_unlock(&chip->state_lock);

	return ret;
}
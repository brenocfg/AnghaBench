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
struct pa12203001_data {int /*<<< orphan*/  map; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_LIGHT 129 
#define  IIO_PROXIMITY 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 unsigned int PA12203001_AFSR_MASK ; 
 int /*<<< orphan*/  PA12203001_ALS_EN_MASK ; 
 int /*<<< orphan*/  PA12203001_PX_EN_MASK ; 
 int /*<<< orphan*/  PA12203001_REG_ADL ; 
 int /*<<< orphan*/  PA12203001_REG_CFG0 ; 
 int /*<<< orphan*/  PA12203001_REG_PDH ; 
 struct pa12203001_data* iio_priv (struct iio_dev*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int* pa12203001_scales ; 
 int pa12203001_set_power_state (struct pa12203001_data*,int,int /*<<< orphan*/ ) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int pa12203001_read_raw(struct iio_dev *indio_dev,
			       struct iio_chan_spec const *chan, int *val,
			       int *val2, long mask)
{
	struct pa12203001_data *data = iio_priv(indio_dev);
	int ret;
	u8 dev_mask;
	unsigned int reg_byte;
	__le16 reg_word;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_LIGHT:
			dev_mask = PA12203001_ALS_EN_MASK;
			ret = pa12203001_set_power_state(data, true, dev_mask);
			if (ret < 0)
				return ret;
			/*
			 * ALS ADC value is stored in registers
			 * PA12203001_REG_ADL and in PA12203001_REG_ADL + 1.
			 */
			ret = regmap_bulk_read(data->map, PA12203001_REG_ADL,
					       &reg_word, 2);
			if (ret < 0)
				goto reg_err;

			*val = le16_to_cpu(reg_word);
			ret = pa12203001_set_power_state(data, false, dev_mask);
			if (ret < 0)
				return ret;
			break;
		case IIO_PROXIMITY:
			dev_mask = PA12203001_PX_EN_MASK;
			ret = pa12203001_set_power_state(data, true, dev_mask);
			if (ret < 0)
				return ret;
			ret = regmap_read(data->map, PA12203001_REG_PDH,
					  &reg_byte);
			if (ret < 0)
				goto reg_err;

			*val = reg_byte;
			ret = pa12203001_set_power_state(data, false, dev_mask);
			if (ret < 0)
				return ret;
			break;
		default:
			return -EINVAL;
		}
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		ret = regmap_read(data->map, PA12203001_REG_CFG0, &reg_byte);
		if (ret < 0)
			return ret;
		*val = 0;
		reg_byte = (reg_byte & PA12203001_AFSR_MASK);
		*val2 = pa12203001_scales[reg_byte >> 4];
		return IIO_VAL_INT_PLUS_MICRO;
	default:
		return -EINVAL;
	}

reg_err:
	pa12203001_set_power_state(data, false, dev_mask);
	return ret;
}
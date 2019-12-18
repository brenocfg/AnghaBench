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
typedef  int u8 ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int address; int channel; size_t differential; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  d32; int /*<<< orphan*/ * d8; } ;
struct ad7746_chip_info {int config; int /*<<< orphan*/  lock; int /*<<< orphan*/ ** capdac; int /*<<< orphan*/  client; TYPE_1__ data; } ;

/* Variables and functions */
 int AD7746_CAPDAC_DACP (int /*<<< orphan*/ ) ; 
 int AD7746_CONF_CAPFS_MASK ; 
 int AD7746_CONF_CAPFS_SHIFT ; 
 int AD7746_CONF_MODE_SINGLE_CONV ; 
 int AD7746_CONF_VTFS_MASK ; 
 int AD7746_CONF_VTFS_SHIFT ; 
 int AD7746_REG_CAP_GAINH ; 
 int AD7746_REG_CAP_OFFH ; 
 int /*<<< orphan*/  AD7746_REG_CFG ; 
 int AD7746_REG_VOLT_GAINH ; 
 int EINVAL ; 
#define  IIO_CAPACITANCE 137 
#define  IIO_CHAN_INFO_CALIBBIAS 136 
#define  IIO_CHAN_INFO_CALIBSCALE 135 
#define  IIO_CHAN_INFO_OFFSET 134 
#define  IIO_CHAN_INFO_PROCESSED 133 
#define  IIO_CHAN_INFO_RAW 132 
#define  IIO_CHAN_INFO_SAMP_FREQ 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_TEMP 129 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int IIO_VAL_INT_PLUS_NANO ; 
#define  IIO_VOLTAGE 128 
 int** ad7746_cap_filter_rate_table ; 
 int ad7746_select_channel (struct iio_dev*,struct iio_chan_spec const*) ; 
 int** ad7746_vt_filter_rate_table ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_i2c_block_data (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int i2c_smbus_read_word_swapped (int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ad7746_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad7746_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val, int *val2,
			   long mask)
{
	struct ad7746_chip_info *chip = iio_priv(indio_dev);
	int ret, delay, idx;
	u8 regval, reg;

	mutex_lock(&chip->lock);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
	case IIO_CHAN_INFO_PROCESSED:
		ret = ad7746_select_channel(indio_dev, chan);
		if (ret < 0)
			goto out;
		delay = ret;

		regval = chip->config | AD7746_CONF_MODE_SINGLE_CONV;
		ret = i2c_smbus_write_byte_data(chip->client, AD7746_REG_CFG,
						regval);
		if (ret < 0)
			goto out;

		msleep(delay);
		/* Now read the actual register */

		ret = i2c_smbus_read_i2c_block_data(chip->client,
						    chan->address >> 8, 3,
						    &chip->data.d8[1]);

		if (ret < 0)
			goto out;

		*val = (be32_to_cpu(chip->data.d32) & 0xFFFFFF) - 0x800000;

		switch (chan->type) {
		case IIO_TEMP:
		/*
		 * temperature in milli degrees Celsius
		 * T = ((*val / 2048) - 4096) * 1000
		 */
			*val = (*val * 125) / 256;
			break;
		case IIO_VOLTAGE:
			if (chan->channel == 1) /* supply_raw*/
				*val = *val * 6;
			break;
		default:
			break;
		}

		ret = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_CALIBSCALE:
		switch (chan->type) {
		case IIO_CAPACITANCE:
			reg = AD7746_REG_CAP_GAINH;
			break;
		case IIO_VOLTAGE:
			reg = AD7746_REG_VOLT_GAINH;
			break;
		default:
			ret = -EINVAL;
			goto out;
		}

		ret = i2c_smbus_read_word_swapped(chip->client, reg);
		if (ret < 0)
			goto out;
		/* 1 + gain_val / 2^16 */
		*val = 1;
		*val2 = (15625 * ret) / 1024;

		ret = IIO_VAL_INT_PLUS_MICRO;
		break;
	case IIO_CHAN_INFO_CALIBBIAS:
		ret = i2c_smbus_read_word_swapped(chip->client,
						  AD7746_REG_CAP_OFFH);
		if (ret < 0)
			goto out;
		*val = ret;

		ret = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_OFFSET:
		*val = AD7746_CAPDAC_DACP(chip->capdac[chan->channel]
					  [chan->differential]) * 338646;

		ret = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_CAPACITANCE:
			/* 8.192pf / 2^24 */
			*val =  0;
			*val2 = 488;
			ret = IIO_VAL_INT_PLUS_NANO;
			break;
		case IIO_VOLTAGE:
			/* 1170mV / 2^23 */
			*val = 1170;
			*val2 = 23;
			ret = IIO_VAL_FRACTIONAL_LOG2;
			break;
		default:
			ret = -EINVAL;
			break;
		}

		break;
	case IIO_CHAN_INFO_SAMP_FREQ:
		switch (chan->type) {
		case IIO_CAPACITANCE:
			idx = (chip->config & AD7746_CONF_CAPFS_MASK) >>
				AD7746_CONF_CAPFS_SHIFT;
			*val = ad7746_cap_filter_rate_table[idx][0];
			ret = IIO_VAL_INT;
			break;
		case IIO_VOLTAGE:
			idx = (chip->config & AD7746_CONF_VTFS_MASK) >>
				AD7746_CONF_VTFS_SHIFT;
			*val = ad7746_vt_filter_rate_table[idx][0];
			ret = IIO_VAL_INT;
			break;
		default:
			ret = -EINVAL;
		}
		break;
	default:
		ret = -EINVAL;
	}
out:
	mutex_unlock(&chip->lock);
	return ret;
}
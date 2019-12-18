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
typedef  scalar_t__ u8 ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int type; int address; size_t channel; } ;
struct ad7746_chip_info {int vt_setup; int config; size_t capdac_set; scalar_t__** capdac; int cap_setup; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int AD7746_CAPSETUP_CAPEN ; 
 int AD7746_CONF_CAPFS_MASK ; 
 int AD7746_CONF_CAPFS_SHIFT ; 
 int AD7746_CONF_VTFS_MASK ; 
 int AD7746_CONF_VTFS_SHIFT ; 
 int /*<<< orphan*/  AD7746_REG_CAPDACA ; 
 int /*<<< orphan*/  AD7746_REG_CAPDACB ; 
 int /*<<< orphan*/  AD7746_REG_CAP_SETUP ; 
 int /*<<< orphan*/  AD7746_REG_VT_SETUP ; 
 int AD7746_VTSETUP_VTEN ; 
 int EINVAL ; 
#define  IIO_CAPACITANCE 130 
#define  IIO_TEMP 129 
#define  IIO_VOLTAGE 128 
 int** ad7746_cap_filter_rate_table ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct ad7746_chip_info* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad7746_select_channel(struct iio_dev *indio_dev,
				 struct iio_chan_spec const *chan)
{
	struct ad7746_chip_info *chip = iio_priv(indio_dev);
	u8 vt_setup, cap_setup;
	int ret, delay, idx;

	switch (chan->type) {
	case IIO_CAPACITANCE:
		cap_setup = (chan->address & 0xFF) | AD7746_CAPSETUP_CAPEN;
		vt_setup = chip->vt_setup & ~AD7746_VTSETUP_VTEN;
		idx = (chip->config & AD7746_CONF_CAPFS_MASK) >>
			AD7746_CONF_CAPFS_SHIFT;
		delay = ad7746_cap_filter_rate_table[idx][1];

		if (chip->capdac_set != chan->channel) {
			ret = i2c_smbus_write_byte_data(chip->client,
				AD7746_REG_CAPDACA,
				chip->capdac[chan->channel][0]);
			if (ret < 0)
				return ret;
			ret = i2c_smbus_write_byte_data(chip->client,
				AD7746_REG_CAPDACB,
				chip->capdac[chan->channel][1]);
			if (ret < 0)
				return ret;

			chip->capdac_set = chan->channel;
		}
		break;
	case IIO_VOLTAGE:
	case IIO_TEMP:
		vt_setup = (chan->address & 0xFF) | AD7746_VTSETUP_VTEN;
		cap_setup = chip->cap_setup & ~AD7746_CAPSETUP_CAPEN;
		idx = (chip->config & AD7746_CONF_VTFS_MASK) >>
			AD7746_CONF_VTFS_SHIFT;
		delay = ad7746_cap_filter_rate_table[idx][1];
		break;
	default:
		return -EINVAL;
	}

	if (chip->cap_setup != cap_setup) {
		ret = i2c_smbus_write_byte_data(chip->client,
						AD7746_REG_CAP_SETUP,
						cap_setup);
		if (ret < 0)
			return ret;

		chip->cap_setup = cap_setup;
	}

	if (chip->vt_setup != vt_setup) {
		ret = i2c_smbus_write_byte_data(chip->client,
						AD7746_REG_VT_SETUP,
						vt_setup);
		if (ret < 0)
			return ret;

		chip->vt_setup = vt_setup;
	}

	return delay;
}
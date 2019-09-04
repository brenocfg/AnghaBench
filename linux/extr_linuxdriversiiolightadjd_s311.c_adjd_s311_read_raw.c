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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  address; } ;
struct adjd_s311_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int ADJD_S311_CAP_MASK ; 
 int /*<<< orphan*/  ADJD_S311_CAP_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADJD_S311_DATA_REG (int /*<<< orphan*/ ) ; 
 int ADJD_S311_INT_MASK ; 
 int /*<<< orphan*/  ADJD_S311_INT_REG (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_HARDWAREGAIN 130 
#define  IIO_CHAN_INFO_INT_TIME 129 
#define  IIO_CHAN_INFO_RAW 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int adjd_s311_read_data (struct iio_dev*,int /*<<< orphan*/ ,int*) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_word_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adjd_s311_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int adjd_s311_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val, int *val2, long mask)
{
	struct adjd_s311_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = adjd_s311_read_data(indio_dev,
			ADJD_S311_DATA_REG(chan->address), val);
		if (ret < 0)
			return ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_HARDWAREGAIN:
		ret = i2c_smbus_read_byte_data(data->client,
			ADJD_S311_CAP_REG(chan->address));
		if (ret < 0)
			return ret;
		*val = ret & ADJD_S311_CAP_MASK;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_INT_TIME:
		ret = i2c_smbus_read_word_data(data->client,
			ADJD_S311_INT_REG(chan->address));
		if (ret < 0)
			return ret;
		*val = 0;
		/*
		 * not documented, based on measurement:
		 * 4095 LSBs correspond to roughly 4 ms
		 */
		*val2 = ret & ADJD_S311_INT_MASK;
		return IIO_VAL_INT_PLUS_MICRO;
	}
	return -EINVAL;
}
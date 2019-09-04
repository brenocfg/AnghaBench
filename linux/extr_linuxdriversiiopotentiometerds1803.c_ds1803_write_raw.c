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
struct iio_chan_spec {int channel; } ;
struct ds1803_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int DS1803_MAX_POS ; 
 int /*<<< orphan*/  DS1803_WRITE (int) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 128 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ds1803_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ds1803_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	struct ds1803_data *data = iio_priv(indio_dev);
	int pot = chan->channel;

	if (val2 != 0)
		return -EINVAL;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (val > DS1803_MAX_POS || val < 0)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	return i2c_smbus_write_byte_data(data->client, DS1803_WRITE(pot), val);
}
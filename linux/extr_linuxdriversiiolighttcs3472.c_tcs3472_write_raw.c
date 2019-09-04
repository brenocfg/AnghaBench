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
struct tcs3472_data {int control; int atime; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBSCALE 129 
#define  IIO_CHAN_INFO_INT_TIME 128 
 int /*<<< orphan*/  TCS3472_ATIME ; 
 int /*<<< orphan*/  TCS3472_CONTROL ; 
 int TCS3472_CONTROL_AGAIN_MASK ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct tcs3472_data* iio_priv (struct iio_dev*) ; 
 int* tcs3472_agains ; 

__attribute__((used)) static int tcs3472_write_raw(struct iio_dev *indio_dev,
			       struct iio_chan_spec const *chan,
			       int val, int val2, long mask)
{
	struct tcs3472_data *data = iio_priv(indio_dev);
	int i;

	switch (mask) {
	case IIO_CHAN_INFO_CALIBSCALE:
		if (val2 != 0)
			return -EINVAL;
		for (i = 0; i < ARRAY_SIZE(tcs3472_agains); i++) {
			if (val == tcs3472_agains[i]) {
				data->control &= ~TCS3472_CONTROL_AGAIN_MASK;
				data->control |= i;
				return i2c_smbus_write_byte_data(
					data->client, TCS3472_CONTROL,
					data->control);
			}
		}
		return -EINVAL;
	case IIO_CHAN_INFO_INT_TIME:
		if (val != 0)
			return -EINVAL;
		for (i = 0; i < 256; i++) {
			if (val2 == (256 - i) * 2400) {
				data->atime = i;
				return i2c_smbus_write_byte_data(
					data->client, TCS3472_ATIME,
					data->atime);
			}

		}
		return -EINVAL;
	}
	return -EINVAL;
}
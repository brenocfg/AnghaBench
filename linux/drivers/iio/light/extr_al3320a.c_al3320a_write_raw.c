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
struct iio_chan_spec {int dummy; } ;
struct al3320a_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int AL3320A_GAIN_SHIFT ; 
 int /*<<< orphan*/  AL3320A_REG_CONFIG_RANGE ; 
 int ARRAY_SIZE (int**) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_SCALE 128 
 int** al3320a_scales ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct al3320a_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int al3320a_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan, int val,
			     int val2, long mask)
{
	struct al3320a_data *data = iio_priv(indio_dev);
	int i;

	switch (mask) {
	case IIO_CHAN_INFO_SCALE:
		for (i = 0; i < ARRAY_SIZE(al3320a_scales); i++) {
			if (val == al3320a_scales[i][0] &&
			    val2 == al3320a_scales[i][1])
				return i2c_smbus_write_byte_data(data->client,
					AL3320A_REG_CONFIG_RANGE,
					i << AL3320A_GAIN_SHIFT);
		}
		break;
	}
	return -EINVAL;
}
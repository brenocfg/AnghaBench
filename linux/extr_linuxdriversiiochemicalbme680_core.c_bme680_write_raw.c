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
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
struct bme680_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OVERSAMPLING_RATIO 131 
#define  IIO_HUMIDITYRELATIVE 130 
#define  IIO_PRESSURE 129 
#define  IIO_TEMP 128 
 int bme680_write_oversampling_ratio_humid (struct bme680_data*,int) ; 
 int bme680_write_oversampling_ratio_press (struct bme680_data*,int) ; 
 int bme680_write_oversampling_ratio_temp (struct bme680_data*,int) ; 
 struct bme680_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int bme680_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val, int val2, long mask)
{
	struct bme680_data *data = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		switch (chan->type) {
		case IIO_TEMP:
			return bme680_write_oversampling_ratio_temp(data, val);
		case IIO_PRESSURE:
			return bme680_write_oversampling_ratio_press(data, val);
		case IIO_HUMIDITYRELATIVE:
			return bme680_write_oversampling_ratio_humid(data, val);
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}
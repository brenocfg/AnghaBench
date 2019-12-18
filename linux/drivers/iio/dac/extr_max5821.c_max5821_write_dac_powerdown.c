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
struct max5821_data {int* powerdown; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t channel; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct max5821_data* iio_priv (struct iio_dev*) ; 
 int max5821_sync_powerdown_mode (struct max5821_data*,struct iio_chan_spec const*) ; 
 int strtobool (char const*,int*) ; 

__attribute__((used)) static ssize_t max5821_write_dac_powerdown(struct iio_dev *indio_dev,
					   uintptr_t private,
					   const struct iio_chan_spec *chan,
					   const char *buf, size_t len)
{
	struct max5821_data *data = iio_priv(indio_dev);
	bool powerdown;
	int ret;

	ret = strtobool(buf, &powerdown);
	if (ret)
		return ret;

	data->powerdown[chan->channel] = powerdown;

	ret = max5821_sync_powerdown_mode(data, chan);
	if (ret < 0)
		return ret;

	return len;
}
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
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ad5755_set_channel_pwr_down (struct iio_dev*,int /*<<< orphan*/ ,int) ; 
 int strtobool (char const*,int*) ; 

__attribute__((used)) static ssize_t ad5755_write_powerdown(struct iio_dev *indio_dev, uintptr_t priv,
	struct iio_chan_spec const *chan, const char *buf, size_t len)
{
	bool pwr_down;
	int ret;

	ret = strtobool(buf, &pwr_down);
	if (ret)
		return ret;

	ret = ad5755_set_channel_pwr_down(indio_dev, chan->channel, pwr_down);
	return ret ? ret : len;
}
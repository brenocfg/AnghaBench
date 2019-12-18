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
struct ltc2632_state {int powerdown_cache_mask; int /*<<< orphan*/  spi_dev; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int channel; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LTC2632_CMD_POWERDOWN_DAC_N ; 
 struct ltc2632_state* iio_priv (struct iio_dev*) ; 
 int ltc2632_spi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strtobool (char const*,int*) ; 

__attribute__((used)) static ssize_t ltc2632_write_dac_powerdown(struct iio_dev *indio_dev,
					   uintptr_t private,
					   const struct iio_chan_spec *chan,
					   const char *buf,
					   size_t len)
{
	bool pwr_down;
	int ret;
	struct ltc2632_state *st = iio_priv(indio_dev);

	ret = strtobool(buf, &pwr_down);
	if (ret)
		return ret;

	if (pwr_down)
		st->powerdown_cache_mask |= (1 << chan->channel);
	else
		st->powerdown_cache_mask &= ~(1 << chan->channel);

	ret = ltc2632_spi_write(st->spi_dev,
				LTC2632_CMD_POWERDOWN_DAC_N,
				chan->channel, 0, 0);

	return ret ? ret : len;
}
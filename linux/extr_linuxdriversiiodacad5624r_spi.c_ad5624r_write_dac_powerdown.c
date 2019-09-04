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
struct ad5624r_state {int pwr_down_mask; int pwr_down_mode; int /*<<< orphan*/  us; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AD5624R_CMD_POWERDOWN_DAC ; 
 int ad5624r_spi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct ad5624r_state* iio_priv (struct iio_dev*) ; 
 int strtobool (char const*,int*) ; 

__attribute__((used)) static ssize_t ad5624r_write_dac_powerdown(struct iio_dev *indio_dev,
	uintptr_t private, const struct iio_chan_spec *chan, const char *buf,
	size_t len)
{
	bool pwr_down;
	int ret;
	struct ad5624r_state *st = iio_priv(indio_dev);

	ret = strtobool(buf, &pwr_down);
	if (ret)
		return ret;

	if (pwr_down)
		st->pwr_down_mask |= (1 << chan->channel);
	else
		st->pwr_down_mask &= ~(1 << chan->channel);

	ret = ad5624r_spi_write(st->us, AD5624R_CMD_POWERDOWN_DAC, 0,
				(st->pwr_down_mode << 4) |
				st->pwr_down_mask, 16);

	return ret ? ret : len;
}
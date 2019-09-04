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
struct ad5791_state {int ctrl; scalar_t__ pwr_down_mode; int pwr_down; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AD5791_ADDR_CTRL ; 
 int AD5791_CTRL_DACTRI ; 
 int AD5791_CTRL_OPGND ; 
 scalar_t__ AD5791_DAC_PWRDN_3STATE ; 
 scalar_t__ AD5791_DAC_PWRDN_6K ; 
 int ad5791_spi_write (struct ad5791_state*,int /*<<< orphan*/ ,int) ; 
 struct ad5791_state* iio_priv (struct iio_dev*) ; 
 int strtobool (char const*,int*) ; 

__attribute__((used)) static ssize_t ad5791_write_dac_powerdown(struct iio_dev *indio_dev,
	 uintptr_t private, const struct iio_chan_spec *chan, const char *buf,
	 size_t len)
{
	bool pwr_down;
	int ret;
	struct ad5791_state *st = iio_priv(indio_dev);

	ret = strtobool(buf, &pwr_down);
	if (ret)
		return ret;

	if (!pwr_down) {
		st->ctrl &= ~(AD5791_CTRL_OPGND | AD5791_CTRL_DACTRI);
	} else {
		if (st->pwr_down_mode == AD5791_DAC_PWRDN_6K)
			st->ctrl |= AD5791_CTRL_OPGND;
		else if (st->pwr_down_mode == AD5791_DAC_PWRDN_3STATE)
			st->ctrl |= AD5791_CTRL_DACTRI;
	}
	st->pwr_down = pwr_down;

	ret = ad5791_spi_write(st, AD5791_ADDR_CTRL, st->ctrl);

	return ret ? ret : len;
}
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
typedef  int uint16_t ;
struct iio_dev {int dummy; } ;
struct adis16480 {scalar_t__ clk_mode; int clk_freq; int /*<<< orphan*/  adis; } ;

/* Variables and functions */
 scalar_t__ ADIS16480_CLK_PPS ; 
 unsigned int ADIS16480_REG_DEC_RATE ; 
 unsigned int ADIS16495_REG_SYNC_SCALE ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int adis_read_reg_16 (int /*<<< orphan*/ *,unsigned int,int*) ; 
 struct adis16480* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int adis16480_get_freq(struct iio_dev *indio_dev, int *val, int *val2)
{
	struct adis16480 *st = iio_priv(indio_dev);
	uint16_t t;
	int ret;
	unsigned freq;
	unsigned int reg;

	if (st->clk_mode == ADIS16480_CLK_PPS)
		reg = ADIS16495_REG_SYNC_SCALE;
	else
		reg = ADIS16480_REG_DEC_RATE;

	ret = adis_read_reg_16(&st->adis, reg, &t);
	if (ret < 0)
		return ret;

	/*
	 * When using PPS mode, the rate of data collection is equal to the
	 * product of the external clock frequency and the scale factor in the
	 * SYNC_SCALE register.
	 * When using sync mode, or internal clock, the output data rate is
	 * equal with  the clock frequency divided by DEC_RATE + 1.
	 */
	if (st->clk_mode == ADIS16480_CLK_PPS)
		freq = st->clk_freq * t;
	else
		freq = st->clk_freq / (t + 1);

	*val = freq / 1000;
	*val2 = (freq % 1000) * 1000;

	return IIO_VAL_INT_PLUS_MICRO;
}
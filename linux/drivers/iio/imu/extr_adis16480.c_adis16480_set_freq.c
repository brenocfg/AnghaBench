#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {int dummy; } ;
struct adis16480 {scalar_t__ clk_mode; unsigned int clk_freq; int /*<<< orphan*/  adis; TYPE_1__* chip_info; } ;
struct TYPE_2__ {unsigned int max_dec_rate; } ;

/* Variables and functions */
 scalar_t__ ADIS16480_CLK_PPS ; 
 unsigned int ADIS16480_REG_DEC_RATE ; 
 unsigned int ADIS16495_REG_SYNC_SCALE ; 
 int EINVAL ; 
 int adis_write_reg_16 (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 struct adis16480* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int adis16480_set_freq(struct iio_dev *indio_dev, int val, int val2)
{
	struct adis16480 *st = iio_priv(indio_dev);
	unsigned int t, reg;

	if (val < 0 || val2 < 0)
		return -EINVAL;

	t =  val * 1000 + val2 / 1000;
	if (t == 0)
		return -EINVAL;

	/*
	 * When using PPS mode, the rate of data collection is equal to the
	 * product of the external clock frequency and the scale factor in the
	 * SYNC_SCALE register.
	 * When using sync mode, or internal clock, the output data rate is
	 * equal with  the clock frequency divided by DEC_RATE + 1.
	 */
	if (st->clk_mode == ADIS16480_CLK_PPS) {
		t = t / st->clk_freq;
		reg = ADIS16495_REG_SYNC_SCALE;
	} else {
		t = st->clk_freq / t;
		reg = ADIS16480_REG_DEC_RATE;
	}

	if (t > st->chip_info->max_dec_rate)
		t = st->chip_info->max_dec_rate;

	if ((t != 0) && (st->clk_mode != ADIS16480_CLK_PPS))
		t--;

	return adis_write_reg_16(&st->adis, reg, t);
}
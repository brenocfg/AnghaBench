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
struct xadc {int dummy; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 long IIO_CHAN_INFO_SAMP_FREQ ; 
 int /*<<< orphan*/  XADC_CONF2_DIV_MASK ; 
 unsigned int XADC_CONF2_DIV_OFFSET ; 
 int /*<<< orphan*/  XADC_REG_CONF2 ; 
 struct xadc* iio_priv (struct iio_dev*) ; 
 unsigned long xadc_get_dclk_rate (struct xadc*) ; 
 int xadc_update_adc_reg (struct xadc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int xadc_write_raw(struct iio_dev *indio_dev,
	struct iio_chan_spec const *chan, int val, int val2, long info)
{
	struct xadc *xadc = iio_priv(indio_dev);
	unsigned long clk_rate = xadc_get_dclk_rate(xadc);
	unsigned int div;

	if (!clk_rate)
		return -EINVAL;

	if (info != IIO_CHAN_INFO_SAMP_FREQ)
		return -EINVAL;

	if (val <= 0)
		return -EINVAL;

	/* Max. 150 kSPS */
	if (val > 150000)
		val = 150000;

	val *= 26;

	/* Min 1MHz */
	if (val < 1000000)
		val = 1000000;

	/*
	 * We want to round down, but only if we do not exceed the 150 kSPS
	 * limit.
	 */
	div = clk_rate / val;
	if (clk_rate / div / 26 > 150000)
		div++;
	if (div < 2)
		div = 2;
	else if (div > 0xff)
		div = 0xff;

	return xadc_update_adc_reg(xadc, XADC_REG_CONF2, XADC_CONF2_DIV_MASK,
		div << XADC_CONF2_DIV_OFFSET);
}
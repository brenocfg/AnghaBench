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
struct lpc32xx_adc_state {int value; int /*<<< orphan*/  vref; int /*<<< orphan*/  clk; int /*<<< orphan*/  completion; int /*<<< orphan*/  adc_base; } ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct iio_chan_spec {int address; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  LPC32XXAD_CTRL (int /*<<< orphan*/ ) ; 
 int LPC32XXAD_INTERNAL ; 
 int LPC32XXAD_PDN_CTRL ; 
 int LPC32XXAD_REFm ; 
 int LPC32XXAD_REFp ; 
 int /*<<< orphan*/  LPC32XXAD_SELECT (int /*<<< orphan*/ ) ; 
 int LPC32XXAD_STROBE ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct lpc32xx_adc_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpc32xx_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val,
			    int *val2,
			    long mask)
{
	struct lpc32xx_adc_state *st = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&indio_dev->mlock);
		ret = clk_prepare_enable(st->clk);
		if (ret) {
			mutex_unlock(&indio_dev->mlock);
			return ret;
		}
		/* Measurement setup */
		__raw_writel(LPC32XXAD_INTERNAL | (chan->address) |
			     LPC32XXAD_REFp | LPC32XXAD_REFm,
			     LPC32XXAD_SELECT(st->adc_base));
		/* Trigger conversion */
		__raw_writel(LPC32XXAD_PDN_CTRL | LPC32XXAD_STROBE,
			     LPC32XXAD_CTRL(st->adc_base));
		wait_for_completion(&st->completion); /* set by ISR */
		clk_disable_unprepare(st->clk);
		*val = st->value;
		mutex_unlock(&indio_dev->mlock);

		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		*val = regulator_get_voltage(st->vref) / 1000;
		*val2 =  10;

		return IIO_VAL_FRACTIONAL_LOG2;
	default:
		return -EINVAL;
	}
}
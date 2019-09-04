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
typedef  int u32 ;
struct stm32_timer_trigger {int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_ENABLE 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  TIM_CNT ; 
 int /*<<< orphan*/  TIM_CR1 ; 
 int TIM_CR1_CEN ; 
 int /*<<< orphan*/  TIM_SMCR ; 
 int TIM_SMCR_SMS ; 
 struct stm32_timer_trigger* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int stm32_counter_read_raw(struct iio_dev *indio_dev,
				  struct iio_chan_spec const *chan,
				  int *val, int *val2, long mask)
{
	struct stm32_timer_trigger *priv = iio_priv(indio_dev);
	u32 dat;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		regmap_read(priv->regmap, TIM_CNT, &dat);
		*val = dat;
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_ENABLE:
		regmap_read(priv->regmap, TIM_CR1, &dat);
		*val = (dat & TIM_CR1_CEN) ? 1 : 0;
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		regmap_read(priv->regmap, TIM_SMCR, &dat);
		dat &= TIM_SMCR_SMS;

		*val = 1;
		*val2 = 0;

		/* in quadrature case scale = 0.25 */
		if (dat == 3)
			*val2 = 2;

		return IIO_VAL_FRACTIONAL_LOG2;
	}

	return -EINVAL;
}
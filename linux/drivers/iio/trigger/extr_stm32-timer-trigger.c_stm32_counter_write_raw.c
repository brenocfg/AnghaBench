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
struct stm32_timer_trigger {int /*<<< orphan*/  clk; int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_ENABLE 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int /*<<< orphan*/  TIM_CNT ; 
 int /*<<< orphan*/  TIM_CR1 ; 
 int TIM_CR1_CEN ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 struct stm32_timer_trigger* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stm32_counter_write_raw(struct iio_dev *indio_dev,
				   struct iio_chan_spec const *chan,
				   int val, int val2, long mask)
{
	struct stm32_timer_trigger *priv = iio_priv(indio_dev);
	u32 dat;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		return regmap_write(priv->regmap, TIM_CNT, val);

	case IIO_CHAN_INFO_SCALE:
		/* fixed scale */
		return -EINVAL;

	case IIO_CHAN_INFO_ENABLE:
		if (val) {
			regmap_read(priv->regmap, TIM_CR1, &dat);
			if (!(dat & TIM_CR1_CEN))
				clk_enable(priv->clk);
			regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN,
					   TIM_CR1_CEN);
		} else {
			regmap_read(priv->regmap, TIM_CR1, &dat);
			regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN,
					   0);
			if (dat & TIM_CR1_CEN)
				clk_disable(priv->clk);
		}
		return 0;
	}

	return -EINVAL;
}
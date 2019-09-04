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
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  TIM_CR1 ; 
 int /*<<< orphan*/  TIM_CR1_DIR ; 
 int /*<<< orphan*/  TIM_SMCR ; 
 int TIM_SMCR_SMS ; 
 struct stm32_timer_trigger* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_quadrature_modes ; 

__attribute__((used)) static int stm32_set_count_direction(struct iio_dev *indio_dev,
				     const struct iio_chan_spec *chan,
				     unsigned int dir)
{
	struct stm32_timer_trigger *priv = iio_priv(indio_dev);
	u32 val;
	int mode;

	/* In encoder mode, direction is RO (given by TI1/TI2 signals) */
	regmap_read(priv->regmap, TIM_SMCR, &val);
	mode = (val & TIM_SMCR_SMS) - 1;
	if ((mode >= 0) || (mode < ARRAY_SIZE(stm32_quadrature_modes)))
		return -EBUSY;

	return regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_DIR,
				  dir ? TIM_CR1_DIR : 0);
}
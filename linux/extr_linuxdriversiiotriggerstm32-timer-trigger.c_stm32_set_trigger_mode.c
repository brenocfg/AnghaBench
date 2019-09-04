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
struct stm32_timer_trigger {int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIM_SMCR ; 
 int /*<<< orphan*/  TIM_SMCR_SMS ; 
 struct stm32_timer_trigger* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_set_trigger_mode(struct iio_dev *indio_dev,
				  const struct iio_chan_spec *chan,
				  unsigned int mode)
{
	struct stm32_timer_trigger *priv = iio_priv(indio_dev);

	regmap_update_bits(priv->regmap, TIM_SMCR, TIM_SMCR_SMS, TIM_SMCR_SMS);

	return 0;
}
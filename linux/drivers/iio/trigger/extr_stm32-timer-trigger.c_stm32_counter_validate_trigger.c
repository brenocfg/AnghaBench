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
struct stm32_timer_trigger {char** valids; int /*<<< orphan*/  regmap; } ;
struct iio_trigger {int /*<<< orphan*/  name; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TIM_SMCR ; 
 int /*<<< orphan*/  TIM_SMCR_TS ; 
 unsigned int TIM_SMCR_TS_SHIFT ; 
 struct stm32_timer_trigger* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  is_stm32_timer_trigger (struct iio_trigger*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_counter_validate_trigger(struct iio_dev *indio_dev,
					  struct iio_trigger *trig)
{
	struct stm32_timer_trigger *priv = iio_priv(indio_dev);
	const char * const *cur = priv->valids;
	unsigned int i = 0;

	if (!is_stm32_timer_trigger(trig))
		return -EINVAL;

	while (cur && *cur) {
		if (!strncmp(trig->name, *cur, strlen(trig->name))) {
			regmap_update_bits(priv->regmap,
					   TIM_SMCR, TIM_SMCR_TS,
					   i << TIM_SMCR_TS_SHIFT);
			return 0;
		}
		cur++;
		i++;
	}

	return -EINVAL;
}
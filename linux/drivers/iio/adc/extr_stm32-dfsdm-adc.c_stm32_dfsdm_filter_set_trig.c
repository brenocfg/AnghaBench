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
typedef  int u32 ;
struct stm32_dfsdm_adc {TYPE_1__* dfsdm; } ;
struct regmap {int dummy; } ;
struct iio_trigger {int dummy; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFSDM_CR1 (unsigned int) ; 
 int DFSDM_CR1_JEXTEN (int) ; 
 int DFSDM_CR1_JEXTEN_MASK ; 
 int DFSDM_CR1_JEXTSEL (int) ; 
 int DFSDM_CR1_JEXTSEL_MASK ; 
 int STM32_DFSDM_JEXTEN_DISABLED ; 
 int STM32_DFSDM_JEXTEN_RISING_EDGE ; 
 struct iio_dev* iio_priv_to_dev (struct stm32_dfsdm_adc*) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 
 int stm32_dfsdm_get_jextsel (struct iio_dev*,struct iio_trigger*) ; 

__attribute__((used)) static int stm32_dfsdm_filter_set_trig(struct stm32_dfsdm_adc *adc,
				       unsigned int fl_id,
				       struct iio_trigger *trig)
{
	struct iio_dev *indio_dev = iio_priv_to_dev(adc);
	struct regmap *regmap = adc->dfsdm->regmap;
	u32 jextsel = 0, jexten = STM32_DFSDM_JEXTEN_DISABLED;
	int ret;

	if (trig) {
		ret = stm32_dfsdm_get_jextsel(indio_dev, trig);
		if (ret < 0)
			return ret;

		/* set trigger source and polarity (default to rising edge) */
		jextsel = ret;
		jexten = STM32_DFSDM_JEXTEN_RISING_EDGE;
	}

	ret = regmap_update_bits(regmap, DFSDM_CR1(fl_id),
				 DFSDM_CR1_JEXTSEL_MASK | DFSDM_CR1_JEXTEN_MASK,
				 DFSDM_CR1_JEXTSEL(jextsel) |
				 DFSDM_CR1_JEXTEN(jexten));
	if (ret < 0)
		return ret;

	return 0;
}
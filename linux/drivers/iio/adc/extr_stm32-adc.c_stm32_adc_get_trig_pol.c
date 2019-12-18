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
struct stm32_adc {int trigger_polarity; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 struct stm32_adc* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int stm32_adc_get_trig_pol(struct iio_dev *indio_dev,
				  const struct iio_chan_spec *chan)
{
	struct stm32_adc *adc = iio_priv(indio_dev);

	return adc->trigger_polarity;
}
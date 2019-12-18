#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stm32_adc {TYPE_1__* cfg; } ;
struct iio_trigger {int /*<<< orphan*/  name; } ;
struct iio_dev {int dummy; } ;
struct TYPE_4__ {int extsel; scalar_t__ name; } ;
struct TYPE_3__ {TYPE_2__* trigs; } ;

/* Variables and functions */
 int EINVAL ; 
 struct stm32_adc* iio_priv (struct iio_dev*) ; 
 scalar_t__ is_stm32_lptim_trigger (struct iio_trigger*) ; 
 scalar_t__ is_stm32_timer_trigger (struct iio_trigger*) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_adc_get_trig_extsel(struct iio_dev *indio_dev,
				     struct iio_trigger *trig)
{
	struct stm32_adc *adc = iio_priv(indio_dev);
	int i;

	/* lookup triggers registered by stm32 timer trigger driver */
	for (i = 0; adc->cfg->trigs[i].name; i++) {
		/**
		 * Checking both stm32 timer trigger type and trig name
		 * should be safe against arbitrary trigger names.
		 */
		if ((is_stm32_timer_trigger(trig) ||
		     is_stm32_lptim_trigger(trig)) &&
		    !strcmp(adc->cfg->trigs[i].name, trig->name)) {
			return adc->cfg->trigs[i].extsel;
		}
	}

	return -EINVAL;
}
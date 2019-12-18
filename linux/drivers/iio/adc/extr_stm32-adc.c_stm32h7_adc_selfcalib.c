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
struct TYPE_2__ {scalar_t__ calibrated; } ;
struct stm32_adc {TYPE_1__ cal; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int STM32H7_ADCAL ; 
 int STM32H7_ADCALDIF ; 
 int STM32H7_ADCALLIN ; 
 int /*<<< orphan*/  STM32H7_ADC_CALIB_TIMEOUT_US ; 
 int /*<<< orphan*/  STM32H7_ADC_CR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* iio_priv_to_dev (struct stm32_adc*) ; 
 int /*<<< orphan*/  stm32_adc_clr_bits (struct stm32_adc*,int /*<<< orphan*/ ,int) ; 
 int stm32_adc_readl_poll_timeout (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_adc_set_bits (struct stm32_adc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stm32h7_adc_selfcalib(struct stm32_adc *adc)
{
	struct iio_dev *indio_dev = iio_priv_to_dev(adc);
	int ret;
	u32 val;

	if (adc->cal.calibrated)
		return true;

	/*
	 * Select calibration mode:
	 * - Offset calibration for single ended inputs
	 * - No linearity calibration (do it later, before reading it)
	 */
	stm32_adc_clr_bits(adc, STM32H7_ADC_CR, STM32H7_ADCALDIF);
	stm32_adc_clr_bits(adc, STM32H7_ADC_CR, STM32H7_ADCALLIN);

	/* Start calibration, then wait for completion */
	stm32_adc_set_bits(adc, STM32H7_ADC_CR, STM32H7_ADCAL);
	ret = stm32_adc_readl_poll_timeout(STM32H7_ADC_CR, val,
					   !(val & STM32H7_ADCAL), 100,
					   STM32H7_ADC_CALIB_TIMEOUT_US);
	if (ret) {
		dev_err(&indio_dev->dev, "calibration failed\n");
		goto out;
	}

	/*
	 * Select calibration mode, then start calibration:
	 * - Offset calibration for differential input
	 * - Linearity calibration (needs to be done only once for single/diff)
	 *   will run simultaneously with offset calibration.
	 */
	stm32_adc_set_bits(adc, STM32H7_ADC_CR,
			   STM32H7_ADCALDIF | STM32H7_ADCALLIN);
	stm32_adc_set_bits(adc, STM32H7_ADC_CR, STM32H7_ADCAL);
	ret = stm32_adc_readl_poll_timeout(STM32H7_ADC_CR, val,
					   !(val & STM32H7_ADCAL), 100,
					   STM32H7_ADC_CALIB_TIMEOUT_US);
	if (ret) {
		dev_err(&indio_dev->dev, "calibration failed\n");
		goto out;
	}

out:
	stm32_adc_clr_bits(adc, STM32H7_ADC_CR,
			   STM32H7_ADCALDIF | STM32H7_ADCALLIN);

	return ret;
}
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
struct TYPE_2__ {int* lincalfact; int calfact_s; int calfact_d; int calibrated; } ;
struct stm32_adc {TYPE_1__ cal; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  STM32H7_ADC_CALFACT ; 
 int /*<<< orphan*/  STM32H7_ADC_CALFACT2 ; 
 int /*<<< orphan*/  STM32H7_ADC_CR ; 
 int STM32H7_CALFACT_D_MASK ; 
 int STM32H7_CALFACT_D_SHIFT ; 
 int STM32H7_CALFACT_S_MASK ; 
 int STM32H7_CALFACT_S_SHIFT ; 
 int STM32H7_LINCALFACT_MASK ; 
 int STM32H7_LINCALFACT_NUM ; 
 int STM32H7_LINCALFACT_SHIFT ; 
 int STM32H7_LINCALRDYW6 ; 
 int /*<<< orphan*/  STM32_ADC_TIMEOUT_US ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* iio_priv_to_dev (struct stm32_adc*) ; 
 int /*<<< orphan*/  stm32_adc_clr_bits (struct stm32_adc*,int /*<<< orphan*/ ,int) ; 
 int stm32_adc_readl (struct stm32_adc*,int /*<<< orphan*/ ) ; 
 int stm32_adc_readl_poll_timeout (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32h7_adc_read_selfcalib(struct stm32_adc *adc)
{
	struct iio_dev *indio_dev = iio_priv_to_dev(adc);
	int i, ret;
	u32 lincalrdyw_mask, val;

	/* Read linearity calibration */
	lincalrdyw_mask = STM32H7_LINCALRDYW6;
	for (i = STM32H7_LINCALFACT_NUM - 1; i >= 0; i--) {
		/* Clear STM32H7_LINCALRDYW[6..1]: transfer calib to CALFACT2 */
		stm32_adc_clr_bits(adc, STM32H7_ADC_CR, lincalrdyw_mask);

		/* Poll: wait calib data to be ready in CALFACT2 register */
		ret = stm32_adc_readl_poll_timeout(STM32H7_ADC_CR, val,
						   !(val & lincalrdyw_mask),
						   100, STM32_ADC_TIMEOUT_US);
		if (ret) {
			dev_err(&indio_dev->dev, "Failed to read calfact\n");
			return ret;
		}

		val = stm32_adc_readl(adc, STM32H7_ADC_CALFACT2);
		adc->cal.lincalfact[i] = (val & STM32H7_LINCALFACT_MASK);
		adc->cal.lincalfact[i] >>= STM32H7_LINCALFACT_SHIFT;

		lincalrdyw_mask >>= 1;
	}

	/* Read offset calibration */
	val = stm32_adc_readl(adc, STM32H7_ADC_CALFACT);
	adc->cal.calfact_s = (val & STM32H7_CALFACT_S_MASK);
	adc->cal.calfact_s >>= STM32H7_CALFACT_S_SHIFT;
	adc->cal.calfact_d = (val & STM32H7_CALFACT_D_MASK);
	adc->cal.calfact_d >>= STM32H7_CALFACT_D_SHIFT;
	adc->cal.calibrated = true;

	return 0;
}
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
struct stm32_adc {int /*<<< orphan*/  pcsel; int /*<<< orphan*/  difsel; } ;

/* Variables and functions */
 int /*<<< orphan*/  STM32H7_ADC_DIFSEL ; 
 int /*<<< orphan*/  STM32H7_ADC_PCSEL ; 
 int /*<<< orphan*/  stm32_adc_writel (struct stm32_adc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32h7_adc_disable (struct stm32_adc*) ; 
 int stm32h7_adc_enable (struct stm32_adc*) ; 
 int /*<<< orphan*/  stm32h7_adc_enter_pwr_down (struct stm32_adc*) ; 
 int stm32h7_adc_exit_pwr_down (struct stm32_adc*) ; 
 int stm32h7_adc_read_selfcalib (struct stm32_adc*) ; 
 int stm32h7_adc_restore_selfcalib (struct stm32_adc*) ; 
 int stm32h7_adc_selfcalib (struct stm32_adc*) ; 

__attribute__((used)) static int stm32h7_adc_prepare(struct stm32_adc *adc)
{
	int calib, ret;

	ret = stm32h7_adc_exit_pwr_down(adc);
	if (ret)
		return ret;

	ret = stm32h7_adc_selfcalib(adc);
	if (ret < 0)
		goto pwr_dwn;
	calib = ret;

	stm32_adc_writel(adc, STM32H7_ADC_DIFSEL, adc->difsel);

	ret = stm32h7_adc_enable(adc);
	if (ret)
		goto pwr_dwn;

	/* Either restore or read calibration result for future reference */
	if (calib)
		ret = stm32h7_adc_restore_selfcalib(adc);
	else
		ret = stm32h7_adc_read_selfcalib(adc);
	if (ret)
		goto disable;

	stm32_adc_writel(adc, STM32H7_ADC_PCSEL, adc->pcsel);

	return 0;

disable:
	stm32h7_adc_disable(adc);
pwr_dwn:
	stm32h7_adc_enter_pwr_down(adc);

	return ret;
}
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
struct stm32_adc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STM32H7_ADC_CR ; 
 int /*<<< orphan*/  STM32H7_BOOST ; 
 int /*<<< orphan*/  STM32H7_DEEPPWD ; 
 int /*<<< orphan*/  stm32_adc_clr_bits (struct stm32_adc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_adc_set_bits (struct stm32_adc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32h7_adc_enter_pwr_down(struct stm32_adc *adc)
{
	stm32_adc_clr_bits(adc, STM32H7_ADC_CR, STM32H7_BOOST);

	/* Setting DEEPPWD disables ADC vreg and clears ADVREGEN */
	stm32_adc_set_bits(adc, STM32H7_ADC_CR, STM32H7_DEEPPWD);
}
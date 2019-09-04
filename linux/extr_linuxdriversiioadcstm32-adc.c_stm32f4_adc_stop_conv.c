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
 int /*<<< orphan*/  STM32F4_ADC_CR1 ; 
 int /*<<< orphan*/  STM32F4_ADC_CR2 ; 
 int /*<<< orphan*/  STM32F4_ADC_SR ; 
 int STM32F4_ADON ; 
 int STM32F4_DDS ; 
 int STM32F4_DMA ; 
 int STM32F4_EXTEN_MASK ; 
 int STM32F4_SCAN ; 
 int STM32F4_STRT ; 
 int /*<<< orphan*/  stm32_adc_clr_bits (struct stm32_adc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stm32f4_adc_stop_conv(struct stm32_adc *adc)
{
	stm32_adc_clr_bits(adc, STM32F4_ADC_CR2, STM32F4_EXTEN_MASK);
	stm32_adc_clr_bits(adc, STM32F4_ADC_SR, STM32F4_STRT);

	stm32_adc_clr_bits(adc, STM32F4_ADC_CR1, STM32F4_SCAN);
	stm32_adc_clr_bits(adc, STM32F4_ADC_CR2,
			   STM32F4_ADON | STM32F4_DMA | STM32F4_DDS);
}
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
 int STM32F4_ADON ; 
 int STM32F4_DDS ; 
 int STM32F4_DMA ; 
 int STM32F4_EOCS ; 
 int STM32F4_EXTEN_MASK ; 
 int STM32F4_SCAN ; 
 int STM32F4_SWSTART ; 
 int stm32_adc_readl (struct stm32_adc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_adc_set_bits (struct stm32_adc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void stm32f4_adc_start_conv(struct stm32_adc *adc, bool dma)
{
	stm32_adc_set_bits(adc, STM32F4_ADC_CR1, STM32F4_SCAN);

	if (dma)
		stm32_adc_set_bits(adc, STM32F4_ADC_CR2,
				   STM32F4_DMA | STM32F4_DDS);

	stm32_adc_set_bits(adc, STM32F4_ADC_CR2, STM32F4_EOCS | STM32F4_ADON);

	/* Wait for Power-up time (tSTAB from datasheet) */
	usleep_range(2, 3);

	/* Software start ? (e.g. trigger detection disabled ?) */
	if (!(stm32_adc_readl(adc, STM32F4_ADC_CR2) & STM32F4_EXTEN_MASK))
		stm32_adc_set_bits(adc, STM32F4_ADC_CR2, STM32F4_SWSTART);
}
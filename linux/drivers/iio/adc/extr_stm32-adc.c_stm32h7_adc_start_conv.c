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
typedef  int u32 ;
struct stm32_adc {int /*<<< orphan*/  lock; } ;
typedef  enum stm32h7_adc_dmngt { ____Placeholder_stm32h7_adc_dmngt } stm32h7_adc_dmngt ;

/* Variables and functions */
 int /*<<< orphan*/  STM32H7_ADC_CFGR ; 
 int /*<<< orphan*/  STM32H7_ADC_CR ; 
 int /*<<< orphan*/  STM32H7_ADSTART ; 
 int STM32H7_DMNGT_DMA_CIRC ; 
 int STM32H7_DMNGT_DR_ONLY ; 
 int STM32H7_DMNGT_MASK ; 
 int STM32H7_DMNGT_SHIFT ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stm32_adc_readl (struct stm32_adc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_adc_set_bits (struct stm32_adc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_adc_writel (struct stm32_adc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stm32h7_adc_start_conv(struct stm32_adc *adc, bool dma)
{
	enum stm32h7_adc_dmngt dmngt;
	unsigned long flags;
	u32 val;

	if (dma)
		dmngt = STM32H7_DMNGT_DMA_CIRC;
	else
		dmngt = STM32H7_DMNGT_DR_ONLY;

	spin_lock_irqsave(&adc->lock, flags);
	val = stm32_adc_readl(adc, STM32H7_ADC_CFGR);
	val = (val & ~STM32H7_DMNGT_MASK) | (dmngt << STM32H7_DMNGT_SHIFT);
	stm32_adc_writel(adc, STM32H7_ADC_CFGR, val);
	spin_unlock_irqrestore(&adc->lock, flags);

	stm32_adc_set_bits(adc, STM32H7_ADC_CR, STM32H7_ADSTART);
}
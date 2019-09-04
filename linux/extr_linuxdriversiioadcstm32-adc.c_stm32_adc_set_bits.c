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

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stm32_adc_readl (struct stm32_adc*,int) ; 
 int /*<<< orphan*/  stm32_adc_writel (struct stm32_adc*,int,int) ; 

__attribute__((used)) static void stm32_adc_set_bits(struct stm32_adc *adc, u32 reg, u32 bits)
{
	unsigned long flags;

	spin_lock_irqsave(&adc->lock, flags);
	stm32_adc_writel(adc, reg, stm32_adc_readl(adc, reg) | bits);
	spin_unlock_irqrestore(&adc->lock, flags);
}
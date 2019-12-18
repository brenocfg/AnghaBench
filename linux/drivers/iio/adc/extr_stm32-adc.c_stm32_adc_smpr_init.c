#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct stm32_adc_regs {unsigned int shift; unsigned int mask; unsigned int reg; } ;
struct stm32_adc {unsigned int* smpr_val; TYPE_3__* cfg; TYPE_2__* common; } ;
struct TYPE_6__ {unsigned int* smp_cycles; TYPE_1__* regs; } ;
struct TYPE_5__ {unsigned int rate; } ;
struct TYPE_4__ {struct stm32_adc_regs* smp_bits; } ;

/* Variables and functions */
 unsigned int NSEC_PER_SEC ; 
 unsigned int STM32_ADC_MAX_SMP ; 

__attribute__((used)) static void stm32_adc_smpr_init(struct stm32_adc *adc, int channel, u32 smp_ns)
{
	const struct stm32_adc_regs *smpr = &adc->cfg->regs->smp_bits[channel];
	u32 period_ns, shift = smpr->shift, mask = smpr->mask;
	unsigned int smp, r = smpr->reg;

	/* Determine sampling time (ADC clock cycles) */
	period_ns = NSEC_PER_SEC / adc->common->rate;
	for (smp = 0; smp <= STM32_ADC_MAX_SMP; smp++)
		if ((period_ns * adc->cfg->smp_cycles[smp]) >= smp_ns)
			break;
	if (smp > STM32_ADC_MAX_SMP)
		smp = STM32_ADC_MAX_SMP;

	/* pre-build sampling time registers (e.g. smpr1, smpr2) */
	adc->smpr_val[r] = (adc->smpr_val[r] & ~mask) | (smp << shift);
}
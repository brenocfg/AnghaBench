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
struct stm32_adc {TYPE_3__* cfg; } ;
struct TYPE_6__ {TYPE_2__* regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; } ;
struct TYPE_5__ {TYPE_1__ ier_eoc; } ;

/* Variables and functions */
 int /*<<< orphan*/  stm32_adc_clr_bits (struct stm32_adc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_adc_conv_irq_disable(struct stm32_adc *adc)
{
	stm32_adc_clr_bits(adc, adc->cfg->regs->ier_eoc.reg,
			   adc->cfg->regs->ier_eoc.mask);
}
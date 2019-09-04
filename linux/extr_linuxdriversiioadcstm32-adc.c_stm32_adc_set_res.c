#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct stm32_adc_regs {int mask; int shift; int /*<<< orphan*/  reg; } ;
struct stm32_adc {int res; TYPE_2__* cfg; } ;
struct TYPE_4__ {TYPE_1__* regs; } ;
struct TYPE_3__ {struct stm32_adc_regs res; } ;

/* Variables and functions */
 int stm32_adc_readl (struct stm32_adc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_adc_writel (struct stm32_adc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stm32_adc_set_res(struct stm32_adc *adc)
{
	const struct stm32_adc_regs *res = &adc->cfg->regs->res;
	u32 val;

	val = stm32_adc_readl(adc, res->reg);
	val = (val & ~res->mask) | (adc->res << res->shift);
	stm32_adc_writel(adc, res->reg, val);
}
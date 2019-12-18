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
typedef  int uint32_t ;
struct ingenic_adc {int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ JZ_ADC_REG_CFG ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ingenic_adc_set_config(struct ingenic_adc *adc,
				   uint32_t mask,
				   uint32_t val)
{
	uint32_t cfg;

	clk_enable(adc->clk);
	mutex_lock(&adc->lock);

	cfg = readl(adc->base + JZ_ADC_REG_CFG) & ~mask;
	cfg |= val;
	writel(cfg, adc->base + JZ_ADC_REG_CFG);

	mutex_unlock(&adc->lock);
	clk_disable(adc->clk);
}
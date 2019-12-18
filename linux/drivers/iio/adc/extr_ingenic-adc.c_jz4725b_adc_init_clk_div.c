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
struct ingenic_adc {scalar_t__ base; int /*<<< orphan*/  clk; } ;
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned long,int) ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ JZ_ADC_REG_ADCLK ; 
 unsigned int JZ_ADC_REG_ADCLK_CLKDIV10US_LSB ; 
 unsigned int JZ_ADC_REG_ADCLK_CLKDIV_LSB ; 
 unsigned int clamp (unsigned int,unsigned int,unsigned int) ; 
 struct clk* clk_get_parent (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int jz4725b_adc_init_clk_div(struct device *dev, struct ingenic_adc *adc)
{
	struct clk *parent_clk;
	unsigned long parent_rate, rate;
	unsigned int div_main, div_10us;

	parent_clk = clk_get_parent(adc->clk);
	if (!parent_clk) {
		dev_err(dev, "ADC clock has no parent\n");
		return -ENODEV;
	}
	parent_rate = clk_get_rate(parent_clk);

	/*
	 * The JZ4725B ADC works at 500 kHz to 8 MHz.
	 * We pick the highest rate possible.
	 * In practice we typically get 6 MHz, half of the 12 MHz EXT clock.
	 */
	div_main = DIV_ROUND_UP(parent_rate, 8000000);
	div_main = clamp(div_main, 1u, 64u);
	rate = parent_rate / div_main;
	if (rate < 500000 || rate > 8000000) {
		dev_err(dev, "No valid divider for ADC main clock\n");
		return -EINVAL;
	}

	/* We also need a divider that produces a 10us clock. */
	div_10us = DIV_ROUND_UP(rate, 100000);

	writel(((div_10us - 1) << JZ_ADC_REG_ADCLK_CLKDIV10US_LSB) |
	       (div_main - 1) << JZ_ADC_REG_ADCLK_CLKDIV_LSB,
	       adc->base + JZ_ADC_REG_ADCLK);

	return 0;
}
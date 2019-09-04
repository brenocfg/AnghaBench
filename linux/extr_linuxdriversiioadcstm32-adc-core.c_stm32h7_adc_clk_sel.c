#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {unsigned long rate; scalar_t__ base; } ;
struct stm32_adc_priv {TYPE_2__ common; TYPE_1__* cfg; scalar_t__ bclk; scalar_t__ aclk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int ckmode; int presc; int div; } ;
struct TYPE_5__ {unsigned long max_clk_rate_hz; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ STM32H7_ADC_CCR ; 
 int STM32H7_CKMODE_MASK ; 
 int STM32H7_CKMODE_SHIFT ; 
 int STM32H7_PRESC_MASK ; 
 int STM32H7_PRESC_SHIFT ; 
 unsigned long clk_get_rate (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int readl_relaxed (scalar_t__) ; 
 TYPE_3__* stm32h7_adc_ckmodes_spec ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int stm32h7_adc_clk_sel(struct platform_device *pdev,
			       struct stm32_adc_priv *priv)
{
	u32 ckmode, presc, val;
	unsigned long rate;
	int i, div;

	/* stm32h7 bus clock is common for all ADC instances (mandatory) */
	if (!priv->bclk) {
		dev_err(&pdev->dev, "No 'bus' clock found\n");
		return -ENOENT;
	}

	/*
	 * stm32h7 can use either 'bus' or 'adc' clock for analog circuitry.
	 * So, choice is to have bus clock mandatory and adc clock optional.
	 * If optional 'adc' clock has been found, then try to use it first.
	 */
	if (priv->aclk) {
		/*
		 * Asynchronous clock modes (e.g. ckmode == 0)
		 * From spec: PLL output musn't exceed max rate
		 */
		rate = clk_get_rate(priv->aclk);
		if (!rate) {
			dev_err(&pdev->dev, "Invalid adc clock rate: 0\n");
			return -EINVAL;
		}

		for (i = 0; i < ARRAY_SIZE(stm32h7_adc_ckmodes_spec); i++) {
			ckmode = stm32h7_adc_ckmodes_spec[i].ckmode;
			presc = stm32h7_adc_ckmodes_spec[i].presc;
			div = stm32h7_adc_ckmodes_spec[i].div;

			if (ckmode)
				continue;

			if ((rate / div) <= priv->cfg->max_clk_rate_hz)
				goto out;
		}
	}

	/* Synchronous clock modes (e.g. ckmode is 1, 2 or 3) */
	rate = clk_get_rate(priv->bclk);
	if (!rate) {
		dev_err(&pdev->dev, "Invalid bus clock rate: 0\n");
		return -EINVAL;
	}

	for (i = 0; i < ARRAY_SIZE(stm32h7_adc_ckmodes_spec); i++) {
		ckmode = stm32h7_adc_ckmodes_spec[i].ckmode;
		presc = stm32h7_adc_ckmodes_spec[i].presc;
		div = stm32h7_adc_ckmodes_spec[i].div;

		if (!ckmode)
			continue;

		if ((rate / div) <= priv->cfg->max_clk_rate_hz)
			goto out;
	}

	dev_err(&pdev->dev, "adc clk selection failed\n");
	return -EINVAL;

out:
	/* rate used later by each ADC instance to control BOOST mode */
	priv->common.rate = rate / div;

	/* Set common clock mode and prescaler */
	val = readl_relaxed(priv->common.base + STM32H7_ADC_CCR);
	val &= ~(STM32H7_CKMODE_MASK | STM32H7_PRESC_MASK);
	val |= ckmode << STM32H7_CKMODE_SHIFT;
	val |= presc << STM32H7_PRESC_SHIFT;
	writel_relaxed(val, priv->common.base + STM32H7_ADC_CCR);

	dev_dbg(&pdev->dev, "Using %s clock/%d source at %ld kHz\n",
		ckmode ? "bus" : "adc", div, priv->common.rate / 1000);

	return 0;
}
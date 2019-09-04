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
typedef  int /*<<< orphan*/  uint32_t ;
struct jz4740_adc {int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ JZ_REG_ADC_CFG ; 
 struct jz4740_adc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int jz4740_adc_set_config(struct device *dev, uint32_t mask, uint32_t val)
{
	struct jz4740_adc *adc = dev_get_drvdata(dev);
	unsigned long flags;
	uint32_t cfg;

	if (!adc)
		return -ENODEV;

	spin_lock_irqsave(&adc->lock, flags);

	cfg = readl(adc->base + JZ_REG_ADC_CFG);

	cfg &= ~mask;
	cfg |= val;

	writel(cfg, adc->base + JZ_REG_ADC_CFG);

	spin_unlock_irqrestore(&adc->lock, flags);

	return 0;
}
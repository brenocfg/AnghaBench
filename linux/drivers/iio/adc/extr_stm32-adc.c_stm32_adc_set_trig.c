#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct stm32_adc {int trigger_polarity; int /*<<< orphan*/  lock; TYPE_4__* cfg; } ;
struct iio_trigger {int dummy; } ;
struct iio_dev {int dummy; } ;
struct TYPE_8__ {TYPE_3__* regs; } ;
struct TYPE_6__ {int mask; int shift; int /*<<< orphan*/  reg; } ;
struct TYPE_5__ {int mask; int shift; } ;
struct TYPE_7__ {TYPE_2__ exten; TYPE_1__ extsel; } ;

/* Variables and functions */
 int STM32_EXTEN_HWTRIG_RISING_EDGE ; 
 int STM32_EXTEN_SWTRIG ; 
 struct stm32_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stm32_adc_get_trig_extsel (struct iio_dev*,struct iio_trigger*) ; 
 int stm32_adc_readl (struct stm32_adc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_adc_writel (struct stm32_adc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stm32_adc_set_trig(struct iio_dev *indio_dev,
			      struct iio_trigger *trig)
{
	struct stm32_adc *adc = iio_priv(indio_dev);
	u32 val, extsel = 0, exten = STM32_EXTEN_SWTRIG;
	unsigned long flags;
	int ret;

	if (trig) {
		ret = stm32_adc_get_trig_extsel(indio_dev, trig);
		if (ret < 0)
			return ret;

		/* set trigger source and polarity (default to rising edge) */
		extsel = ret;
		exten = adc->trigger_polarity + STM32_EXTEN_HWTRIG_RISING_EDGE;
	}

	spin_lock_irqsave(&adc->lock, flags);
	val = stm32_adc_readl(adc, adc->cfg->regs->exten.reg);
	val &= ~(adc->cfg->regs->exten.mask | adc->cfg->regs->extsel.mask);
	val |= exten << adc->cfg->regs->exten.shift;
	val |= extsel << adc->cfg->regs->extsel.shift;
	stm32_adc_writel(adc,  adc->cfg->regs->exten.reg, val);
	spin_unlock_irqrestore(&adc->lock, flags);

	return 0;
}
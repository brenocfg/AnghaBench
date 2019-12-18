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
struct TYPE_7__ {int mask; int /*<<< orphan*/  reg; } ;
struct stm32_adc_regspec {TYPE_3__ exten; TYPE_2__* sqr; int /*<<< orphan*/ * smpr; } ;
struct stm32_adc {int* smpr_val; int* buffer; TYPE_4__* cfg; int /*<<< orphan*/  completion; scalar_t__ bufi; } ;
struct TYPE_5__ {struct device* parent; } ;
struct iio_dev {TYPE_1__ dev; } ;
struct iio_chan_spec {int channel; } ;
struct device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* stop_conv ) (struct stm32_adc*) ;int /*<<< orphan*/  (* start_conv ) (struct stm32_adc*,int) ;struct stm32_adc_regspec* regs; } ;
struct TYPE_6__ {int mask; int shift; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  STM32_ADC_TIMEOUT ; 
 struct stm32_adc* iio_priv (struct iio_dev*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_adc_clr_bits (struct stm32_adc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stm32_adc_conv_irq_disable (struct stm32_adc*) ; 
 int /*<<< orphan*/  stm32_adc_conv_irq_enable (struct stm32_adc*) ; 
 int stm32_adc_readl (struct stm32_adc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_adc_writel (struct stm32_adc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct stm32_adc*,int) ; 
 int /*<<< orphan*/  stub2 (struct stm32_adc*) ; 
 long wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_adc_single_conv(struct iio_dev *indio_dev,
				 const struct iio_chan_spec *chan,
				 int *res)
{
	struct stm32_adc *adc = iio_priv(indio_dev);
	struct device *dev = indio_dev->dev.parent;
	const struct stm32_adc_regspec *regs = adc->cfg->regs;
	long timeout;
	u32 val;
	int ret;

	reinit_completion(&adc->completion);

	adc->bufi = 0;

	ret = pm_runtime_get_sync(dev);
	if (ret < 0) {
		pm_runtime_put_noidle(dev);
		return ret;
	}

	/* Apply sampling time settings */
	stm32_adc_writel(adc, regs->smpr[0], adc->smpr_val[0]);
	stm32_adc_writel(adc, regs->smpr[1], adc->smpr_val[1]);

	/* Program chan number in regular sequence (SQ1) */
	val = stm32_adc_readl(adc, regs->sqr[1].reg);
	val &= ~regs->sqr[1].mask;
	val |= chan->channel << regs->sqr[1].shift;
	stm32_adc_writel(adc, regs->sqr[1].reg, val);

	/* Set regular sequence len (0 for 1 conversion) */
	stm32_adc_clr_bits(adc, regs->sqr[0].reg, regs->sqr[0].mask);

	/* Trigger detection disabled (conversion can be launched in SW) */
	stm32_adc_clr_bits(adc, regs->exten.reg, regs->exten.mask);

	stm32_adc_conv_irq_enable(adc);

	adc->cfg->start_conv(adc, false);

	timeout = wait_for_completion_interruptible_timeout(
					&adc->completion, STM32_ADC_TIMEOUT);
	if (timeout == 0) {
		ret = -ETIMEDOUT;
	} else if (timeout < 0) {
		ret = timeout;
	} else {
		*res = adc->buffer[0];
		ret = IIO_VAL_INT;
	}

	adc->cfg->stop_conv(adc);

	stm32_adc_conv_irq_disable(adc);

	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);

	return ret;
}
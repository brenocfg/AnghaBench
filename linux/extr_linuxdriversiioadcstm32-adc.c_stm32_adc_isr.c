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
struct TYPE_4__ {int mask; int /*<<< orphan*/  reg; } ;
struct stm32_adc_regspec {int /*<<< orphan*/  dr; TYPE_2__ isr_eoc; } ;
struct stm32_adc {size_t bufi; size_t num_conv; int /*<<< orphan*/  completion; int /*<<< orphan*/ * buffer; TYPE_1__* cfg; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {struct stm32_adc_regspec* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ iio_buffer_enabled (struct iio_dev*) ; 
 struct iio_dev* iio_priv_to_dev (struct stm32_adc*) ; 
 int /*<<< orphan*/  iio_trigger_poll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_adc_conv_irq_disable (struct stm32_adc*) ; 
 int stm32_adc_readl (struct stm32_adc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_adc_readw (struct stm32_adc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t stm32_adc_isr(int irq, void *data)
{
	struct stm32_adc *adc = data;
	struct iio_dev *indio_dev = iio_priv_to_dev(adc);
	const struct stm32_adc_regspec *regs = adc->cfg->regs;
	u32 status = stm32_adc_readl(adc, regs->isr_eoc.reg);

	if (status & regs->isr_eoc.mask) {
		/* Reading DR also clears EOC status flag */
		adc->buffer[adc->bufi] = stm32_adc_readw(adc, regs->dr);
		if (iio_buffer_enabled(indio_dev)) {
			adc->bufi++;
			if (adc->bufi >= adc->num_conv) {
				stm32_adc_conv_irq_disable(adc);
				iio_trigger_poll(indio_dev->trig);
			}
		} else {
			complete(&adc->completion);
		}
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}
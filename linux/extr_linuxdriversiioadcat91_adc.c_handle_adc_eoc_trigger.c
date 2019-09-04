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
struct iio_dev {int /*<<< orphan*/  trig; } ;
struct at91_adc_state {int done; int /*<<< orphan*/  wq_data_avail; int /*<<< orphan*/  chnb; int /*<<< orphan*/  last_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_ADC_CHAN (struct at91_adc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT91_ADC_LCDR ; 
 int /*<<< orphan*/  at91_adc_readl (struct at91_adc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 scalar_t__ iio_buffer_enabled (struct iio_dev*) ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_poll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_adc_eoc_trigger(int irq, struct iio_dev *idev)
{
	struct at91_adc_state *st = iio_priv(idev);

	if (iio_buffer_enabled(idev)) {
		disable_irq_nosync(irq);
		iio_trigger_poll(idev->trig);
	} else {
		st->last_value = at91_adc_readl(st, AT91_ADC_CHAN(st, st->chnb));
		/* Needed to ACK the DRDY interruption */
		at91_adc_readl(st, AT91_ADC_LCDR);
		st->done = true;
		wake_up_interruptible(&st->wq_data_avail);
	}
}
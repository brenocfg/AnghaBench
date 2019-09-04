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
struct iio_poll_func {int /*<<< orphan*/  timestamp; struct iio_dev* indio_dev; } ;
struct iio_dev {int masklength; int /*<<< orphan*/  trig; struct iio_chan_spec* channels; int /*<<< orphan*/  active_scan_mask; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;
struct at91_adc_state {int /*<<< orphan*/  irq; int /*<<< orphan*/ * buffer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_ADC_CHAN (struct at91_adc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT91_ADC_LCDR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  at91_adc_readl (struct at91_adc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t at91_adc_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *idev = pf->indio_dev;
	struct at91_adc_state *st = iio_priv(idev);
	struct iio_chan_spec const *chan;
	int i, j = 0;

	for (i = 0; i < idev->masklength; i++) {
		if (!test_bit(i, idev->active_scan_mask))
			continue;
		chan = idev->channels + i;
		st->buffer[j] = at91_adc_readl(st, AT91_ADC_CHAN(st, chan->channel));
		j++;
	}

	iio_push_to_buffers_with_timestamp(idev, st->buffer, pf->timestamp);

	iio_trigger_notify_done(idev->trig);

	/* Needed to ACK the DRDY interruption */
	at91_adc_readl(st, AT91_ADC_LCDR);

	enable_irq(st->irq);

	return IRQ_HANDLED;
}
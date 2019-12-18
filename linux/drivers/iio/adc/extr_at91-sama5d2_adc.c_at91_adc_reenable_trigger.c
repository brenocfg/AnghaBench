#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iio_trigger {int dummy; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ dma_chan; } ;
struct at91_adc_state {int /*<<< orphan*/  irq; TYPE_1__ dma_st; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_SAMA5D2_LCDR ; 
 int /*<<< orphan*/  at91_adc_readl (struct at91_adc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 
 struct iio_dev* iio_trigger_get_drvdata (struct iio_trigger*) ; 

__attribute__((used)) static int at91_adc_reenable_trigger(struct iio_trigger *trig)
{
	struct iio_dev *indio = iio_trigger_get_drvdata(trig);
	struct at91_adc_state *st = iio_priv(indio);

	/* if we are using DMA, we must not reenable irq after each trigger */
	if (st->dma_st.dma_chan)
		return 0;

	enable_irq(st->irq);

	/* Needed to ACK the DRDY interruption */
	at91_adc_readl(st, AT91_SAMA5D2_LCDR);
	return 0;
}
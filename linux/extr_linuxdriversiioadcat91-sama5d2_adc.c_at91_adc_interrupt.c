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
struct iio_dev {int /*<<< orphan*/  trig; } ;
struct TYPE_3__ {scalar_t__ dma_chan; } ;
struct at91_adc_state {int conversion_done; int /*<<< orphan*/  wq_data_available; TYPE_2__* chan; void* conversion_value; TYPE_1__ dma_st; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int AT91_SAMA5D2_IER_NOPEN ; 
 int AT91_SAMA5D2_IER_PEN ; 
 int AT91_SAMA5D2_IER_PRDY ; 
 int AT91_SAMA5D2_IER_XRDY ; 
 int AT91_SAMA5D2_IER_YRDY ; 
 int /*<<< orphan*/  AT91_SAMA5D2_IMR ; 
 int /*<<< orphan*/  AT91_SAMA5D2_ISR ; 
 int AT91_SAMA5D2_ISR_PENS ; 
 int /*<<< orphan*/  AT91_SAMA5D2_PRESSR ; 
 int /*<<< orphan*/  AT91_SAMA5D2_XPOSR ; 
 int /*<<< orphan*/  AT91_SAMA5D2_YPOSR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  at91_adc_no_pen_detect_interrupt (struct at91_adc_state*) ; 
 int /*<<< orphan*/  at91_adc_pen_detect_interrupt (struct at91_adc_state*) ; 
 void* at91_adc_readl (struct at91_adc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_adc_touch_data_handler (struct iio_dev*) ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 scalar_t__ iio_buffer_enabled (struct iio_dev*) ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_poll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t at91_adc_interrupt(int irq, void *private)
{
	struct iio_dev *indio = private;
	struct at91_adc_state *st = iio_priv(indio);
	u32 status = at91_adc_readl(st, AT91_SAMA5D2_ISR);
	u32 imr = at91_adc_readl(st, AT91_SAMA5D2_IMR);
	u32 rdy_mask = AT91_SAMA5D2_IER_XRDY | AT91_SAMA5D2_IER_YRDY |
			AT91_SAMA5D2_IER_PRDY;

	if (!(status & imr))
		return IRQ_NONE;
	if (status & AT91_SAMA5D2_IER_PEN) {
		/* pen detected IRQ */
		at91_adc_pen_detect_interrupt(st);
	} else if ((status & AT91_SAMA5D2_IER_NOPEN)) {
		/* nopen detected IRQ */
		at91_adc_no_pen_detect_interrupt(st);
	} else if ((status & AT91_SAMA5D2_ISR_PENS) &&
		   ((status & rdy_mask) == rdy_mask)) {
		/* periodic trigger IRQ - during pen sense */
		at91_adc_touch_data_handler(indio);
	} else if (status & AT91_SAMA5D2_ISR_PENS) {
		/*
		 * touching, but the measurements are not ready yet.
		 * read and ignore.
		 */
		status = at91_adc_readl(st, AT91_SAMA5D2_XPOSR);
		status = at91_adc_readl(st, AT91_SAMA5D2_YPOSR);
		status = at91_adc_readl(st, AT91_SAMA5D2_PRESSR);
	} else if (iio_buffer_enabled(indio) && !st->dma_st.dma_chan) {
		/* triggered buffer without DMA */
		disable_irq_nosync(irq);
		iio_trigger_poll(indio->trig);
	} else if (iio_buffer_enabled(indio) && st->dma_st.dma_chan) {
		/* triggered buffer with DMA - should not happen */
		disable_irq_nosync(irq);
		WARN(true, "Unexpected irq occurred\n");
	} else if (!iio_buffer_enabled(indio)) {
		/* software requested conversion */
		st->conversion_value = at91_adc_readl(st, st->chan->address);
		st->conversion_done = true;
		wake_up_interruptible(&st->wq_data_available);
	}
	return IRQ_HANDLED;
}
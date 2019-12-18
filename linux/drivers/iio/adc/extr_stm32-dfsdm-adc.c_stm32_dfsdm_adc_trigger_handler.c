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
struct stm32_dfsdm_adc {size_t bufi; size_t buf_sz; int /*<<< orphan*/ * rx_buf; } ;
struct iio_poll_func {int /*<<< orphan*/  timestamp; struct iio_dev* indio_dev; } ;
struct iio_dev {int scan_bytes; int /*<<< orphan*/  trig; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct stm32_dfsdm_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int stm32_dfsdm_adc_dma_residue (struct stm32_dfsdm_adc*) ; 
 int /*<<< orphan*/  stm32_dfsdm_process_data (struct stm32_dfsdm_adc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t stm32_dfsdm_adc_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct stm32_dfsdm_adc *adc = iio_priv(indio_dev);
	int available = stm32_dfsdm_adc_dma_residue(adc);

	while (available >= indio_dev->scan_bytes) {
		s32 *buffer = (s32 *)&adc->rx_buf[adc->bufi];

		stm32_dfsdm_process_data(adc, buffer);

		iio_push_to_buffers_with_timestamp(indio_dev, buffer,
						   pf->timestamp);
		available -= indio_dev->scan_bytes;
		adc->bufi += indio_dev->scan_bytes;
		if (adc->bufi >= adc->buf_sz)
			adc->bufi = 0;
	}

	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}
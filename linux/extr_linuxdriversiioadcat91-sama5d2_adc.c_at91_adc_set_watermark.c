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
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {unsigned int watermark; } ;
struct at91_adc_state {TYPE_1__ dma_st; TYPE_2__* selected_trig; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw_trig; } ;

/* Variables and functions */
 unsigned int AT91_HWFIFO_MAX_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  at91_adc_dma_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_adc_dma_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  to_platform_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int at91_adc_set_watermark(struct iio_dev *indio_dev, unsigned int val)
{
	struct at91_adc_state *st = iio_priv(indio_dev);

	if (val > AT91_HWFIFO_MAX_SIZE)
		return -EINVAL;

	if (!st->selected_trig->hw_trig) {
		dev_dbg(&indio_dev->dev, "we need hw trigger for DMA\n");
		return 0;
	}

	dev_dbg(&indio_dev->dev, "new watermark is %u\n", val);
	st->dma_st.watermark = val;

	/*
	 * The logic here is: if we have watermark 1, it means we do
	 * each conversion with it's own IRQ, thus we don't need DMA.
	 * If the watermark is higher, we do DMA to do all the transfers in bulk
	 */

	if (val == 1)
		at91_adc_dma_disable(to_platform_device(&indio_dev->dev));
	else if (val > 1)
		at91_adc_dma_init(to_platform_device(&indio_dev->dev));

	return 0;
}
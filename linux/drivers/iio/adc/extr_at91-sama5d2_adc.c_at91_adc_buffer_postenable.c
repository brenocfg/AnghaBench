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
struct iio_dev {int currentmode; int /*<<< orphan*/  dev; int /*<<< orphan*/  active_scan_mask; } ;
struct TYPE_2__ {int /*<<< orphan*/  channels_bitmask; } ;
struct at91_adc_state {TYPE_1__ touch_st; } ;

/* Variables and functions */
 scalar_t__ AT91_SAMA5D2_MAX_CHAN_IDX ; 
 int EINVAL ; 
 int INDIO_ALL_TRIGGERED_MODES ; 
 int at91_adc_configure_touch (struct at91_adc_state*,int) ; 
 int at91_adc_dma_start (struct iio_dev*) ; 
 scalar_t__ bitmap_subset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 
 int iio_triggered_buffer_postenable (struct iio_dev*) ; 

__attribute__((used)) static int at91_adc_buffer_postenable(struct iio_dev *indio_dev)
{
	int ret;
	struct at91_adc_state *st = iio_priv(indio_dev);

	/* check if we are enabling triggered buffer or the touchscreen */
	if (bitmap_subset(indio_dev->active_scan_mask,
			  &st->touch_st.channels_bitmask,
			  AT91_SAMA5D2_MAX_CHAN_IDX + 1)) {
		/* touchscreen enabling */
		return at91_adc_configure_touch(st, true);
	}
	/* if we are not in triggered mode, we cannot enable the buffer. */
	if (!(indio_dev->currentmode & INDIO_ALL_TRIGGERED_MODES))
		return -EINVAL;

	/* we continue with the triggered buffer */
	ret = at91_adc_dma_start(indio_dev);
	if (ret) {
		dev_err(&indio_dev->dev, "buffer postenable failed\n");
		return ret;
	}

	return iio_triggered_buffer_postenable(indio_dev);
}
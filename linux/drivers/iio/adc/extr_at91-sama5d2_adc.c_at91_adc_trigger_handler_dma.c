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
typedef  int u32 ;
struct iio_dev {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int rx_buf_sz; int watermark; int dma_ts; size_t buf_idx; int /*<<< orphan*/ * rx_buf; } ;
struct at91_adc_state {TYPE_1__ dma_st; } ;
typedef  int s64 ;

/* Variables and functions */
 int AT91_SAMA5D2_IER_GOVRE ; 
 int /*<<< orphan*/  AT91_SAMA5D2_ISR ; 
 int /*<<< orphan*/  at91_adc_adjust_val_osr_array (struct at91_adc_state*,int /*<<< orphan*/ *,int) ; 
 int at91_adc_dma_size_done (struct at91_adc_state*) ; 
 int at91_adc_readl (struct at91_adc_state*,int /*<<< orphan*/ ) ; 
 int div_s64 (int,int) ; 
 void* iio_get_time_ns (struct iio_dev*) ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void at91_adc_trigger_handler_dma(struct iio_dev *indio_dev)
{
	struct at91_adc_state *st = iio_priv(indio_dev);
	int transferred_len = at91_adc_dma_size_done(st);
	s64 ns = iio_get_time_ns(indio_dev);
	s64 interval;
	int sample_index = 0, sample_count, sample_size;

	u32 status = at91_adc_readl(st, AT91_SAMA5D2_ISR);
	/* if we reached this point, we cannot sample faster */
	if (status & AT91_SAMA5D2_IER_GOVRE)
		pr_info_ratelimited("%s: conversion overrun detected\n",
				    indio_dev->name);

	sample_size = div_s64(st->dma_st.rx_buf_sz, st->dma_st.watermark);

	sample_count = div_s64(transferred_len, sample_size);

	/*
	 * interval between samples is total time since last transfer handling
	 * divided by the number of samples (total size divided by sample size)
	 */
	interval = div_s64((ns - st->dma_st.dma_ts), sample_count);

	while (transferred_len >= sample_size) {
		/*
		 * for all the values in the current sample,
		 * adjust the values inside the buffer for oversampling
		 */
		at91_adc_adjust_val_osr_array(st,
					&st->dma_st.rx_buf[st->dma_st.buf_idx],
					sample_size);

		iio_push_to_buffers_with_timestamp(indio_dev,
				(st->dma_st.rx_buf + st->dma_st.buf_idx),
				(st->dma_st.dma_ts + interval * sample_index));
		/* adjust remaining length */
		transferred_len -= sample_size;
		/* adjust buffer index */
		st->dma_st.buf_idx += sample_size;
		/* in case of reaching end of buffer, reset index */
		if (st->dma_st.buf_idx >= st->dma_st.rx_buf_sz)
			st->dma_st.buf_idx = 0;
		sample_index++;
	}
	/* adjust saved time for next transfer handling */
	st->dma_st.dma_ts = iio_get_time_ns(indio_dev);
}
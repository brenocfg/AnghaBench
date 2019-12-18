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
typedef  int /*<<< orphan*/  u32 ;
struct stm32_dfsdm_adc {unsigned int nconv; void* buf_sz; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int DFSDM_DMA_BUFFER_SIZE ; 
 struct stm32_dfsdm_adc* iio_priv (struct iio_dev*) ; 
 void* min (unsigned int,unsigned int) ; 

__attribute__((used)) static int stm32_dfsdm_set_watermark(struct iio_dev *indio_dev,
				     unsigned int val)
{
	struct stm32_dfsdm_adc *adc = iio_priv(indio_dev);
	unsigned int watermark = DFSDM_DMA_BUFFER_SIZE / 2;
	unsigned int rx_buf_sz = DFSDM_DMA_BUFFER_SIZE;

	/*
	 * DMA cyclic transfers are used, buffer is split into two periods.
	 * There should be :
	 * - always one buffer (period) DMA is working on
	 * - one buffer (period) driver pushed to ASoC side.
	 */
	watermark = min(watermark, val * (unsigned int)(sizeof(u32)));
	adc->buf_sz = min(rx_buf_sz, watermark * 2 * adc->nconv);

	return 0;
}
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
typedef  int /*<<< orphan*/  u8 ;
struct tiadc_dma {int current_period; int period_size; int /*<<< orphan*/ * buf; } ;
struct tiadc_device {struct tiadc_dma dma; } ;
struct iio_dev {scalar_t__ scan_bytes; } ;

/* Variables and functions */
 struct tiadc_device* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers (struct iio_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tiadc_dma_rx_complete(void *param)
{
	struct iio_dev *indio_dev = param;
	struct tiadc_device *adc_dev = iio_priv(indio_dev);
	struct tiadc_dma *dma = &adc_dev->dma;
	u8 *data;
	int i;

	data = dma->buf + dma->current_period * dma->period_size;
	dma->current_period = 1 - dma->current_period; /* swap the buffer ID */

	for (i = 0; i < dma->period_size; i += indio_dev->scan_bytes) {
		iio_push_to_buffers(indio_dev, data);
		data += indio_dev->scan_bytes;
	}
}
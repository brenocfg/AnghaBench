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
typedef  int /*<<< orphan*/  u32 ;
struct tiadc_dma {TYPE_2__* chan; int /*<<< orphan*/  addr; int /*<<< orphan*/  buf; } ;
struct tiadc_device {int /*<<< orphan*/  mfd_tscadc; struct tiadc_dma dma; } ;
struct platform_device {int dummy; } ;
struct iio_dev {int dummy; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BUFFER_SIZE ; 
 int /*<<< orphan*/  am335x_tsc_se_clr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (TYPE_2__*) ; 
 int /*<<< orphan*/  get_adc_step_mask (struct tiadc_device*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct tiadc_device* iio_priv (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tiadc_channels_remove (struct iio_dev*) ; 
 int /*<<< orphan*/  tiadc_iio_buffered_hardware_remove (struct iio_dev*) ; 

__attribute__((used)) static int tiadc_remove(struct platform_device *pdev)
{
	struct iio_dev *indio_dev = platform_get_drvdata(pdev);
	struct tiadc_device *adc_dev = iio_priv(indio_dev);
	struct tiadc_dma *dma = &adc_dev->dma;
	u32 step_en;

	if (dma->chan) {
		dma_free_coherent(dma->chan->device->dev, DMA_BUFFER_SIZE,
				  dma->buf, dma->addr);
		dma_release_channel(dma->chan);
	}
	iio_device_unregister(indio_dev);
	tiadc_iio_buffered_hardware_remove(indio_dev);
	tiadc_channels_remove(indio_dev);

	step_en = get_adc_step_mask(adc_dev);
	am335x_tsc_se_clr(adc_dev->mfd_tscadc, step_en);

	return 0;
}
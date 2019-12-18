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
struct stm32_dfsdm_adc {TYPE_1__* dev_data; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ DFSDM_AUDIO ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct iio_dev* iio_priv_to_dev (struct stm32_dfsdm_adc*) ; 
 int /*<<< orphan*/  of_platform_depopulate (int /*<<< orphan*/ *) ; 
 struct stm32_dfsdm_adc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stm32_dfsdm_dma_release (struct iio_dev*) ; 

__attribute__((used)) static int stm32_dfsdm_adc_remove(struct platform_device *pdev)
{
	struct stm32_dfsdm_adc *adc = platform_get_drvdata(pdev);
	struct iio_dev *indio_dev = iio_priv_to_dev(adc);

	if (adc->dev_data->type == DFSDM_AUDIO)
		of_platform_depopulate(&pdev->dev);
	iio_device_unregister(indio_dev);
	stm32_dfsdm_dma_release(indio_dev);

	return 0;
}
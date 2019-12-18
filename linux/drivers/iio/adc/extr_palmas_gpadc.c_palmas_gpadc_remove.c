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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct palmas_gpadc {int /*<<< orphan*/  irq_auto_1; scalar_t__ wakeup2_enable; int /*<<< orphan*/  irq_auto_0; scalar_t__ wakeup1_enable; int /*<<< orphan*/  irq; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 struct iio_dev* dev_to_iio_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_wakeup_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct palmas_gpadc*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct palmas_gpadc* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int palmas_gpadc_remove(struct platform_device *pdev)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(&pdev->dev);
	struct palmas_gpadc *adc = iio_priv(indio_dev);

	if (adc->wakeup1_enable || adc->wakeup2_enable)
		device_wakeup_disable(&pdev->dev);
	iio_device_unregister(indio_dev);
	free_irq(adc->irq, adc);
	if (adc->wakeup1_enable)
		free_irq(adc->irq_auto_0, adc);
	if (adc->wakeup2_enable)
		free_irq(adc->irq_auto_1, adc);

	return 0;
}
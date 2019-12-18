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
struct platform_device {int dummy; } ;
struct mxs_lradc_adc {int dummy; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct mxs_lradc_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int /*<<< orphan*/  mxs_lradc_adc_hw_stop (struct mxs_lradc_adc*) ; 
 int /*<<< orphan*/  mxs_lradc_adc_trigger_remove (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mxs_lradc_adc_remove(struct platform_device *pdev)
{
	struct iio_dev *iio = platform_get_drvdata(pdev);
	struct mxs_lradc_adc *adc = iio_priv(iio);

	iio_device_unregister(iio);
	mxs_lradc_adc_hw_stop(adc);
	mxs_lradc_adc_trigger_remove(iio);
	iio_triggered_buffer_cleanup(iio);

	return 0;
}
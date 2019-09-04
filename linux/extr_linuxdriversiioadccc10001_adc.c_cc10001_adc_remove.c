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
struct iio_dev {int dummy; } ;
struct cc10001_adc_device {int /*<<< orphan*/  reg; int /*<<< orphan*/  adc_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  cc10001_adc_power_down (struct cc10001_adc_device*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct cc10001_adc_device* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cc10001_adc_remove(struct platform_device *pdev)
{
	struct iio_dev *indio_dev = platform_get_drvdata(pdev);
	struct cc10001_adc_device *adc_dev = iio_priv(indio_dev);

	cc10001_adc_power_down(adc_dev);
	iio_device_unregister(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	clk_disable_unprepare(adc_dev->adc_clk);
	regulator_disable(adc_dev->reg);

	return 0;
}
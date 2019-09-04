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
struct imx7d_adc {int /*<<< orphan*/  vref; int /*<<< orphan*/  clk; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct imx7d_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  imx7d_adc_power_down (struct imx7d_adc*) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx7d_adc_remove(struct platform_device *pdev)
{
	struct iio_dev *indio_dev = platform_get_drvdata(pdev);
	struct imx7d_adc *info = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);

	imx7d_adc_power_down(info);

	clk_disable_unprepare(info->clk);
	regulator_disable(info->vref);

	return 0;
}
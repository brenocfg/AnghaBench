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
struct lpc18xx_adc {int /*<<< orphan*/  vref; int /*<<< orphan*/  clk; scalar_t__ base; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ LPC18XX_ADC_CR ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct lpc18xx_adc* iio_priv (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int lpc18xx_adc_remove(struct platform_device *pdev)
{
	struct iio_dev *indio_dev = platform_get_drvdata(pdev);
	struct lpc18xx_adc *adc = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);

	writel(0, adc->base + LPC18XX_ADC_CR);
	clk_disable_unprepare(adc->clk);
	regulator_disable(adc->vref);

	return 0;
}
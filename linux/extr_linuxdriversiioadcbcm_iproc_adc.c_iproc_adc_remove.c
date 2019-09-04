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
struct iproc_adc_priv {int /*<<< orphan*/  adc_clk; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct iproc_adc_priv* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iproc_adc_disable (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int iproc_adc_remove(struct platform_device *pdev)
{
	struct iio_dev *indio_dev = platform_get_drvdata(pdev);
	struct iproc_adc_priv *adc_priv = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);
	iproc_adc_disable(indio_dev);
	clk_disable_unprepare(adc_priv->adc_clk);

	return 0;
}
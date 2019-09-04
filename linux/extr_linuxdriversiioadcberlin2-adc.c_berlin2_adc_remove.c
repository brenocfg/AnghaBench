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
struct berlin2_adc_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BERLIN2_SM_CTRL ; 
 int /*<<< orphan*/  BERLIN2_SM_CTRL_ADC_POWER ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct berlin2_adc_priv* iio_priv (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int berlin2_adc_remove(struct platform_device *pdev)
{
	struct iio_dev *indio_dev = platform_get_drvdata(pdev);
	struct berlin2_adc_priv *priv = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);

	/* Power down the ADC */
	regmap_update_bits(priv->regmap, BERLIN2_SM_CTRL,
			   BERLIN2_SM_CTRL_ADC_POWER, 0);

	return 0;
}
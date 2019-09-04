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
struct platform_device {int dummy; } ;
struct iio_dev {int dummy; } ;
struct axp20x_adc_iio {int /*<<< orphan*/  regmap; TYPE_1__* data; } ;
struct TYPE_2__ {scalar_t__ adc_en2; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_ADC_EN1 ; 
 int /*<<< orphan*/  AXP20X_ADC_EN2 ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_map_array_unregister (struct iio_dev*) ; 
 struct axp20x_adc_iio* iio_priv (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axp20x_remove(struct platform_device *pdev)
{
	struct iio_dev *indio_dev = platform_get_drvdata(pdev);
	struct axp20x_adc_iio *info = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);
	iio_map_array_unregister(indio_dev);

	regmap_write(info->regmap, AXP20X_ADC_EN1, 0);

	if (info->data->adc_en2)
		regmap_write(info->regmap, AXP20X_ADC_EN2, 0);

	return 0;
}
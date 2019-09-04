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
struct sun4i_gpadc_iio {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUN4I_GPADC_CTRL1 ; 
 int /*<<< orphan*/  SUN4I_GPADC_TPR ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct sun4i_gpadc_iio* iio_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun4i_gpadc_runtime_suspend(struct device *dev)
{
	struct sun4i_gpadc_iio *info = iio_priv(dev_get_drvdata(dev));

	/* Disable the ADC on IP */
	regmap_write(info->regmap, SUN4I_GPADC_CTRL1, 0);
	/* Disable temperature sensor on IP */
	regmap_write(info->regmap, SUN4I_GPADC_TPR, 0);

	return 0;
}
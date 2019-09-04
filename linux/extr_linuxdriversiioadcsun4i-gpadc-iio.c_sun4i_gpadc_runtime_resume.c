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
struct sun4i_gpadc_iio {int /*<<< orphan*/  regmap; TYPE_1__* data; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int tp_mode_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUN4I_GPADC_CTRL0 ; 
 int SUN4I_GPADC_CTRL0_ADC_CLK_DIVIDER (int) ; 
 int SUN4I_GPADC_CTRL0_FS_DIV (int) ; 
 int SUN4I_GPADC_CTRL0_T_ACQ (int) ; 
 int /*<<< orphan*/  SUN4I_GPADC_CTRL1 ; 
 int /*<<< orphan*/  SUN4I_GPADC_CTRL3 ; 
 int SUN4I_GPADC_CTRL3_FILTER_EN ; 
 int SUN4I_GPADC_CTRL3_FILTER_TYPE (int) ; 
 int /*<<< orphan*/  SUN4I_GPADC_TPR ; 
 int SUN4I_GPADC_TPR_TEMP_ENABLE ; 
 int SUN4I_GPADC_TPR_TEMP_PERIOD (int) ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct sun4i_gpadc_iio* iio_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sun4i_gpadc_runtime_resume(struct device *dev)
{
	struct sun4i_gpadc_iio *info = iio_priv(dev_get_drvdata(dev));

	/* clkin = 6MHz */
	regmap_write(info->regmap, SUN4I_GPADC_CTRL0,
		     SUN4I_GPADC_CTRL0_ADC_CLK_DIVIDER(2) |
		     SUN4I_GPADC_CTRL0_FS_DIV(7) |
		     SUN4I_GPADC_CTRL0_T_ACQ(63));
	regmap_write(info->regmap, SUN4I_GPADC_CTRL1, info->data->tp_mode_en);
	regmap_write(info->regmap, SUN4I_GPADC_CTRL3,
		     SUN4I_GPADC_CTRL3_FILTER_EN |
		     SUN4I_GPADC_CTRL3_FILTER_TYPE(1));
	/* period = SUN4I_GPADC_TPR_TEMP_PERIOD * 256 * 16 / clkin; ~0.6s */
	regmap_write(info->regmap, SUN4I_GPADC_TPR,
		     SUN4I_GPADC_TPR_TEMP_ENABLE |
		     SUN4I_GPADC_TPR_TEMP_PERIOD(800));

	return 0;
}
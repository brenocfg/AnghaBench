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
struct sun4i_gpadc_iio {int /*<<< orphan*/  temp_data_irq; int /*<<< orphan*/  regmap; scalar_t__ no_irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct iio_dev {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUN4I_GPADC_TEMP_DATA ; 
 struct sun4i_gpadc_iio* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int sun4i_gpadc_read (struct iio_dev*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun4i_gpadc_temp_read(struct iio_dev *indio_dev, int *val)
{
	struct sun4i_gpadc_iio *info = iio_priv(indio_dev);

	if (info->no_irq) {
		pm_runtime_get_sync(indio_dev->dev.parent);

		regmap_read(info->regmap, SUN4I_GPADC_TEMP_DATA, val);

		pm_runtime_mark_last_busy(indio_dev->dev.parent);
		pm_runtime_put_autosuspend(indio_dev->dev.parent);

		return 0;
	}

	return sun4i_gpadc_read(indio_dev, 0, val, info->temp_data_irq);
}
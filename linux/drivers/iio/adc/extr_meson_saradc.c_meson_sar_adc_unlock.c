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
struct meson_sar_adc_priv {int /*<<< orphan*/  regmap; TYPE_1__* param; } ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct TYPE_2__ {scalar_t__ has_bl30_integration; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESON_SAR_ADC_DELAY ; 
 int /*<<< orphan*/  MESON_SAR_ADC_DELAY_KERNEL_BUSY ; 
 struct meson_sar_adc_priv* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void meson_sar_adc_unlock(struct iio_dev *indio_dev)
{
	struct meson_sar_adc_priv *priv = iio_priv(indio_dev);

	if (priv->param->has_bl30_integration)
		/* allow BL30 to use the SAR ADC again */
		regmap_update_bits(priv->regmap, MESON_SAR_ADC_DELAY,
				MESON_SAR_ADC_DELAY_KERNEL_BUSY, 0);

	mutex_unlock(&indio_dev->mlock);
}
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
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MESON_SAR_ADC_DELAY ; 
 int MESON_SAR_ADC_DELAY_BL30_BUSY ; 
 int /*<<< orphan*/  MESON_SAR_ADC_DELAY_KERNEL_BUSY ; 
 struct meson_sar_adc_priv* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int meson_sar_adc_lock(struct iio_dev *indio_dev)
{
	struct meson_sar_adc_priv *priv = iio_priv(indio_dev);
	int val, timeout = 10000;

	mutex_lock(&indio_dev->mlock);

	if (priv->param->has_bl30_integration) {
		/* prevent BL30 from using the SAR ADC while we are using it */
		regmap_update_bits(priv->regmap, MESON_SAR_ADC_DELAY,
				MESON_SAR_ADC_DELAY_KERNEL_BUSY,
				MESON_SAR_ADC_DELAY_KERNEL_BUSY);

		/*
		 * wait until BL30 releases it's lock (so we can use the SAR
		 * ADC)
		 */
		do {
			udelay(1);
			regmap_read(priv->regmap, MESON_SAR_ADC_DELAY, &val);
		} while (val & MESON_SAR_ADC_DELAY_BL30_BUSY && timeout--);

		if (timeout < 0) {
			mutex_unlock(&indio_dev->mlock);
			return -ETIMEDOUT;
		}
	}

	return 0;
}
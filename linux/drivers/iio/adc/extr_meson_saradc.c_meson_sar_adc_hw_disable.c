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
struct meson_sar_adc_priv {int /*<<< orphan*/  vref; int /*<<< orphan*/  core_clk; int /*<<< orphan*/  regmap; int /*<<< orphan*/  adc_clk; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESON_SAR_ADC_REG3 ; 
 int /*<<< orphan*/  MESON_SAR_ADC_REG3_ADC_EN ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct meson_sar_adc_priv* iio_priv (struct iio_dev*) ; 
 int meson_sar_adc_lock (struct iio_dev*) ; 
 int /*<<< orphan*/  meson_sar_adc_set_bandgap (struct iio_dev*,int) ; 
 int /*<<< orphan*/  meson_sar_adc_unlock (struct iio_dev*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_sar_adc_hw_disable(struct iio_dev *indio_dev)
{
	struct meson_sar_adc_priv *priv = iio_priv(indio_dev);
	int ret;

	ret = meson_sar_adc_lock(indio_dev);
	if (ret)
		return ret;

	clk_disable_unprepare(priv->adc_clk);

	regmap_update_bits(priv->regmap, MESON_SAR_ADC_REG3,
			   MESON_SAR_ADC_REG3_ADC_EN, 0);

	meson_sar_adc_set_bandgap(indio_dev, false);

	clk_disable_unprepare(priv->core_clk);

	regulator_disable(priv->vref);

	meson_sar_adc_unlock(indio_dev);

	return 0;
}
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
typedef  int /*<<< orphan*/  u32 ;
struct meson_sar_adc_priv {int /*<<< orphan*/  vref; int /*<<< orphan*/  core_clk; int /*<<< orphan*/  regmap; int /*<<< orphan*/  adc_clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct iio_dev {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MESON_SAR_ADC_REG0 ; 
 int /*<<< orphan*/  MESON_SAR_ADC_REG0_FIFO_CNT_IRQ_MASK ; 
 int /*<<< orphan*/  MESON_SAR_ADC_REG3 ; 
 int /*<<< orphan*/  MESON_SAR_ADC_REG3_ADC_EN ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct meson_sar_adc_priv* iio_priv (struct iio_dev*) ; 
 int meson_sar_adc_lock (struct iio_dev*) ; 
 int /*<<< orphan*/  meson_sar_adc_set_bandgap (struct iio_dev*,int) ; 
 int /*<<< orphan*/  meson_sar_adc_unlock (struct iio_dev*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int meson_sar_adc_hw_enable(struct iio_dev *indio_dev)
{
	struct meson_sar_adc_priv *priv = iio_priv(indio_dev);
	int ret;
	u32 regval;

	ret = meson_sar_adc_lock(indio_dev);
	if (ret)
		goto err_lock;

	ret = regulator_enable(priv->vref);
	if (ret < 0) {
		dev_err(indio_dev->dev.parent,
			"failed to enable vref regulator\n");
		goto err_vref;
	}

	ret = clk_prepare_enable(priv->core_clk);
	if (ret) {
		dev_err(indio_dev->dev.parent, "failed to enable core clk\n");
		goto err_core_clk;
	}

	regval = FIELD_PREP(MESON_SAR_ADC_REG0_FIFO_CNT_IRQ_MASK, 1);
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_REG0,
			   MESON_SAR_ADC_REG0_FIFO_CNT_IRQ_MASK, regval);

	meson_sar_adc_set_bandgap(indio_dev, true);

	regmap_update_bits(priv->regmap, MESON_SAR_ADC_REG3,
			   MESON_SAR_ADC_REG3_ADC_EN,
			   MESON_SAR_ADC_REG3_ADC_EN);

	udelay(5);

	ret = clk_prepare_enable(priv->adc_clk);
	if (ret) {
		dev_err(indio_dev->dev.parent, "failed to enable adc clk\n");
		goto err_adc_clk;
	}

	meson_sar_adc_unlock(indio_dev);

	return 0;

err_adc_clk:
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_REG3,
			   MESON_SAR_ADC_REG3_ADC_EN, 0);
	meson_sar_adc_set_bandgap(indio_dev, false);
	clk_disable_unprepare(priv->core_clk);
err_core_clk:
	regulator_disable(priv->vref);
err_vref:
	meson_sar_adc_unlock(indio_dev);
err_lock:
	return ret;
}
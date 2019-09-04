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
typedef  int /*<<< orphan*/  u32 ;
struct meson_sar_adc_priv {int /*<<< orphan*/  done; int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MESON_SAR_ADC_REG0 ; 
 int /*<<< orphan*/  MESON_SAR_ADC_REG0_FIFO_CNT_IRQ_MASK ; 
 int /*<<< orphan*/  MESON_SAR_ADC_REG0_FIFO_COUNT_MASK ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct meson_sar_adc_priv* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t meson_sar_adc_irq(int irq, void *data)
{
	struct iio_dev *indio_dev = data;
	struct meson_sar_adc_priv *priv = iio_priv(indio_dev);
	unsigned int cnt, threshold;
	u32 regval;

	regmap_read(priv->regmap, MESON_SAR_ADC_REG0, &regval);
	cnt = FIELD_GET(MESON_SAR_ADC_REG0_FIFO_COUNT_MASK, regval);
	threshold = FIELD_GET(MESON_SAR_ADC_REG0_FIFO_CNT_IRQ_MASK, regval);

	if (cnt < threshold)
		return IRQ_NONE;

	complete(&priv->done);

	return IRQ_HANDLED;
}
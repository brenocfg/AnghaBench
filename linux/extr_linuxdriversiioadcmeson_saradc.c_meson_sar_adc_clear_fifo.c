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
struct meson_sar_adc_priv {int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESON_SAR_ADC_FIFO_RD ; 
 unsigned int MESON_SAR_ADC_MAX_FIFO_SIZE ; 
 struct meson_sar_adc_priv* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  meson_sar_adc_get_fifo_count (struct iio_dev*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static void meson_sar_adc_clear_fifo(struct iio_dev *indio_dev)
{
	struct meson_sar_adc_priv *priv = iio_priv(indio_dev);
	unsigned int count, tmp;

	for (count = 0; count < MESON_SAR_ADC_MAX_FIFO_SIZE; count++) {
		if (!meson_sar_adc_get_fifo_count(indio_dev))
			break;

		regmap_read(priv->regmap, MESON_SAR_ADC_FIFO_RD, &tmp);
	}
}
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
typedef  int u32 ;
struct lpc18xx_dac {int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 128 
 scalar_t__ LPC18XX_DAC_CR ; 
 int LPC18XX_DAC_CR_BIAS ; 
 int LPC18XX_DAC_CR_VALUE_MASK ; 
 int LPC18XX_DAC_CR_VALUE_SHIFT ; 
 scalar_t__ LPC18XX_DAC_CTRL ; 
 int LPC18XX_DAC_CTRL_DMA_ENA ; 
 struct lpc18xx_dac* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int lpc18xx_dac_write_raw(struct iio_dev *indio_dev,
				 struct iio_chan_spec const *chan,
				 int val, int val2, long mask)
{
	struct lpc18xx_dac *dac = iio_priv(indio_dev);
	u32 reg;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (val < 0 || val > LPC18XX_DAC_CR_VALUE_MASK)
			return -EINVAL;

		reg = LPC18XX_DAC_CR_BIAS;
		reg |= val << LPC18XX_DAC_CR_VALUE_SHIFT;

		mutex_lock(&dac->lock);
		writel(reg, dac->base + LPC18XX_DAC_CR);
		writel(LPC18XX_DAC_CTRL_DMA_ENA, dac->base + LPC18XX_DAC_CTRL);
		mutex_unlock(&dac->lock);

		return 0;
	}

	return -EINVAL;
}
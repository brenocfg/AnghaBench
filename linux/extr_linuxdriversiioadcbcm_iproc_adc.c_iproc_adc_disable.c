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
struct iproc_adc_priv {int /*<<< orphan*/  regmap; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPROC_ADC_CONTROLLER_EN ; 
 int /*<<< orphan*/  IPROC_REGCTL2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct iproc_adc_priv* iio_priv (struct iio_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iproc_adc_disable(struct iio_dev *indio_dev)
{
	u32 val;
	int ret;
	struct iproc_adc_priv *adc_priv = iio_priv(indio_dev);

	ret = regmap_read(adc_priv->regmap, IPROC_REGCTL2, &val);
	if (ret) {
		dev_err(&indio_dev->dev,
			"failed to read IPROC_REGCTL2 %d\n", ret);
		return;
	}

	val &= ~IPROC_ADC_CONTROLLER_EN;
	ret = regmap_write(adc_priv->regmap, IPROC_REGCTL2, val);
	if (ret) {
		dev_err(&indio_dev->dev,
			"failed to write IPROC_REGCTL2 %d\n", ret);
		return;
	}
}
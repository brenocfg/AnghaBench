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
struct imx7d_adc {int /*<<< orphan*/  vref; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; } ;
struct iio_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 struct imx7d_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  imx7d_adc_hw_init (struct imx7d_adc*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx7d_adc_enable(struct device *dev)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct imx7d_adc *info = iio_priv(indio_dev);
	int ret;

	ret = regulator_enable(info->vref);
	if (ret) {
		dev_err(info->dev,
			"Can't enable adc reference top voltage, err = %d\n",
			ret);
		return ret;
	}

	ret = clk_prepare_enable(info->clk);
	if (ret) {
		dev_err(info->dev,
			"Could not prepare or enable clock.\n");
		regulator_disable(info->vref);
		return ret;
	}

	imx7d_adc_hw_init(info);

	return 0;
}
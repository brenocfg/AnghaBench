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
struct iio_dev {int dummy; } ;
struct ad7766 {int /*<<< orphan*/  pd_gpio; int /*<<< orphan*/  reg; TYPE_1__* spi; int /*<<< orphan*/  mclk; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ad7766* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7766_preenable(struct iio_dev *indio_dev)
{
	struct ad7766 *ad7766 = iio_priv(indio_dev);
	int ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(ad7766->reg), ad7766->reg);
	if (ret < 0) {
		dev_err(&ad7766->spi->dev, "Failed to enable supplies: %d\n",
			ret);
		return ret;
	}

	ret = clk_prepare_enable(ad7766->mclk);
	if (ret < 0) {
		dev_err(&ad7766->spi->dev, "Failed to enable MCLK: %d\n", ret);
		regulator_bulk_disable(ARRAY_SIZE(ad7766->reg), ad7766->reg);
		return ret;
	}

	gpiod_set_value(ad7766->pd_gpio, 0);

	return 0;
}
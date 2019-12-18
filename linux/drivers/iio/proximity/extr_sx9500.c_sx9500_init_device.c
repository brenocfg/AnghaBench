#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sx9500_data {int /*<<< orphan*/  regmap; scalar_t__ gpiod_rst; } ;
struct iio_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  def; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  SX9500_REG_IRQ_MSK ; 
 int /*<<< orphan*/  SX9500_REG_IRQ_SRC ; 
 int /*<<< orphan*/  SX9500_REG_RESET ; 
 int /*<<< orphan*/  SX9500_SOFT_RESET ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 struct sx9500_data* iio_priv (struct iio_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* sx9500_default_regs ; 
 int sx9500_init_compensation (struct iio_dev*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int sx9500_init_device(struct iio_dev *indio_dev)
{
	struct sx9500_data *data = iio_priv(indio_dev);
	int ret, i;
	unsigned int val;

	if (data->gpiod_rst) {
		gpiod_set_value_cansleep(data->gpiod_rst, 0);
		usleep_range(1000, 2000);
		gpiod_set_value_cansleep(data->gpiod_rst, 1);
		usleep_range(1000, 2000);
	}

	ret = regmap_write(data->regmap, SX9500_REG_IRQ_MSK, 0);
	if (ret < 0)
		return ret;

	ret = regmap_write(data->regmap, SX9500_REG_RESET,
			   SX9500_SOFT_RESET);
	if (ret < 0)
		return ret;

	ret = regmap_read(data->regmap, SX9500_REG_IRQ_SRC, &val);
	if (ret < 0)
		return ret;

	for (i = 0; i < ARRAY_SIZE(sx9500_default_regs); i++) {
		ret = regmap_write(data->regmap,
				   sx9500_default_regs[i].reg,
				   sx9500_default_regs[i].def);
		if (ret < 0)
			return ret;
	}

	return sx9500_init_compensation(indio_dev);
}
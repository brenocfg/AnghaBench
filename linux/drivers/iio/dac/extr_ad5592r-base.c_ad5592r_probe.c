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
struct TYPE_2__ {struct device* parent; } ;
struct iio_dev {char const* name; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct device {scalar_t__ of_node; } ;
struct ad5592r_state {int num_channels; int /*<<< orphan*/ * reg; struct ad5592r_rw_ops const* ops; struct device* dev; } ;
struct ad5592r_rw_ops {int (* reg_write ) (struct ad5592r_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AD5592R_REG_PD ; 
 int /*<<< orphan*/  AD5592R_REG_PD_EN_REF ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int ad5592r_alloc_channels (struct ad5592r_state*) ; 
 int /*<<< orphan*/  ad5592r_get_vref (struct ad5592r_state*) ; 
 int ad5592r_gpio_init (struct ad5592r_state*) ; 
 int /*<<< orphan*/  ad5592r_info ; 
 int /*<<< orphan*/  ad5592r_init_scales (struct ad5592r_state*,int /*<<< orphan*/ ) ; 
 int ad5592r_reset (struct ad5592r_state*) ; 
 int /*<<< orphan*/  ad5592r_reset_channel_modes (struct ad5592r_state*) ; 
 int ad5592r_set_channel_modes (struct ad5592r_state*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct iio_dev*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int /*<<< orphan*/ * devm_regulator_get_optional (struct device*,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct ad5592r_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ *) ; 
 int regulator_enable (int /*<<< orphan*/ *) ; 
 int stub1 (struct ad5592r_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ad5592r_probe(struct device *dev, const char *name,
		const struct ad5592r_rw_ops *ops)
{
	struct iio_dev *iio_dev;
	struct ad5592r_state *st;
	int ret;

	iio_dev = devm_iio_device_alloc(dev, sizeof(*st));
	if (!iio_dev)
		return -ENOMEM;

	st = iio_priv(iio_dev);
	st->dev = dev;
	st->ops = ops;
	st->num_channels = 8;
	dev_set_drvdata(dev, iio_dev);

	st->reg = devm_regulator_get_optional(dev, "vref");
	if (IS_ERR(st->reg)) {
		if ((PTR_ERR(st->reg) != -ENODEV) && dev->of_node)
			return PTR_ERR(st->reg);

		st->reg = NULL;
	} else {
		ret = regulator_enable(st->reg);
		if (ret)
			return ret;
	}

	iio_dev->dev.parent = dev;
	iio_dev->name = name;
	iio_dev->info = &ad5592r_info;
	iio_dev->modes = INDIO_DIRECT_MODE;

	ad5592r_init_scales(st, ad5592r_get_vref(st));

	ret = ad5592r_reset(st);
	if (ret)
		goto error_disable_reg;

	ret = ops->reg_write(st, AD5592R_REG_PD,
		     (st->reg == NULL) ? AD5592R_REG_PD_EN_REF : 0);
	if (ret)
		goto error_disable_reg;

	ret = ad5592r_alloc_channels(st);
	if (ret)
		goto error_disable_reg;

	ret = ad5592r_set_channel_modes(st);
	if (ret)
		goto error_reset_ch_modes;

	ret = iio_device_register(iio_dev);
	if (ret)
		goto error_reset_ch_modes;

	ret = ad5592r_gpio_init(st);
	if (ret)
		goto error_dev_unregister;

	return 0;

error_dev_unregister:
	iio_device_unregister(iio_dev);

error_reset_ch_modes:
	ad5592r_reset_channel_modes(st);

error_disable_reg:
	if (st->reg)
		regulator_disable(st->reg);

	return ret;
}
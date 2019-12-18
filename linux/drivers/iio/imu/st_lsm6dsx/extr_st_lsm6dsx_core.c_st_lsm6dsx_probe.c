#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ addr; } ;
struct st_lsm6dsx_shub_settings {TYPE_2__ master_en; } ;
struct st_lsm6dsx_hw {int irq; int /*<<< orphan*/ * iio_devs; struct device* dev; TYPE_1__* settings; struct regmap* regmap; void* buff; int /*<<< orphan*/  page_lock; int /*<<< orphan*/  conf_lock; int /*<<< orphan*/  fifo_lock; } ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct st_lsm6dsx_shub_settings shub_settings; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ST_LSM6DSX_BUFF_SIZE ; 
 int ST_LSM6DSX_ID_EXT0 ; 
 int ST_LSM6DSX_ID_MAX ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,void*) ; 
 int devm_iio_device_register (struct device*,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st_lsm6dsx_alloc_iiodev (struct st_lsm6dsx_hw*,int,char const*) ; 
 int st_lsm6dsx_check_whoami (struct st_lsm6dsx_hw*,int,char const**) ; 
 int st_lsm6dsx_fifo_setup (struct st_lsm6dsx_hw*) ; 
 int st_lsm6dsx_init_device (struct st_lsm6dsx_hw*) ; 
 int st_lsm6dsx_shub_probe (struct st_lsm6dsx_hw*,char const*) ; 

int st_lsm6dsx_probe(struct device *dev, int irq, int hw_id,
		     struct regmap *regmap)
{
	const struct st_lsm6dsx_shub_settings *hub_settings;
	struct st_lsm6dsx_hw *hw;
	const char *name = NULL;
	int i, err;

	hw = devm_kzalloc(dev, sizeof(*hw), GFP_KERNEL);
	if (!hw)
		return -ENOMEM;

	dev_set_drvdata(dev, (void *)hw);

	mutex_init(&hw->fifo_lock);
	mutex_init(&hw->conf_lock);
	mutex_init(&hw->page_lock);

	hw->buff = devm_kzalloc(dev, ST_LSM6DSX_BUFF_SIZE, GFP_KERNEL);
	if (!hw->buff)
		return -ENOMEM;

	hw->dev = dev;
	hw->irq = irq;
	hw->regmap = regmap;

	err = st_lsm6dsx_check_whoami(hw, hw_id, &name);
	if (err < 0)
		return err;

	for (i = 0; i < ST_LSM6DSX_ID_EXT0; i++) {
		hw->iio_devs[i] = st_lsm6dsx_alloc_iiodev(hw, i, name);
		if (!hw->iio_devs[i])
			return -ENOMEM;
	}

	err = st_lsm6dsx_init_device(hw);
	if (err < 0)
		return err;

	hub_settings = &hw->settings->shub_settings;
	if (hub_settings->master_en.addr) {
		err = st_lsm6dsx_shub_probe(hw, name);
		if (err < 0)
			return err;
	}

	if (hw->irq > 0) {
		err = st_lsm6dsx_fifo_setup(hw);
		if (err < 0)
			return err;
	}

	for (i = 0; i < ST_LSM6DSX_ID_MAX; i++) {
		if (!hw->iio_devs[i])
			continue;

		err = devm_iio_device_register(hw->dev, hw->iio_devs[i]);
		if (err)
			return err;
	}

	return 0;
}
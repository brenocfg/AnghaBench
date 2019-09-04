#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct ad5791_platform_data* platform_data; } ;
struct spi_device {TYPE_3__ dev; } ;
struct TYPE_7__ {TYPE_3__* parent; } ;
struct iio_dev {int num_channels; int /*<<< orphan*/  name; int /*<<< orphan*/ * channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct ad5791_state {int pwr_down; int vref_mv; int vref_neg_mv; int ctrl; void* reg_vdd; void* reg_vss; struct spi_device* spi; TYPE_6__* chip_info; } ;
struct ad5791_platform_data {int vref_pos_mv; int vref_neg_mv; scalar_t__ use_rbuf_gain2; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* get_lin_comp ) (int) ;} ;
struct TYPE_8__ {size_t driver_data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int AD5761_CTRL_LINCOMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AD5791_ADDR_CTRL ; 
 int /*<<< orphan*/  AD5791_ADDR_SW_CTRL ; 
 int AD5791_CTRL_BIN2SC ; 
 int AD5791_CTRL_DACTRI ; 
 int AD5791_CTRL_OPGND ; 
 int AD5791_CTRL_RBUF ; 
 int AD5791_SWCTRL_RESET ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IS_ERR (void*) ; 
 int /*<<< orphan*/ * ad5791_channels ; 
 TYPE_6__* ad5791_chip_info_tbl ; 
 int /*<<< orphan*/  ad5791_info ; 
 int ad5791_spi_write (struct ad5791_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_3__*,int) ; 
 void* devm_regulator_get (TYPE_3__*,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ad5791_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (void*) ; 
 int regulator_enable (void*) ; 
 int regulator_get_voltage (void*) ; 
 TYPE_2__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static int ad5791_probe(struct spi_device *spi)
{
	struct ad5791_platform_data *pdata = spi->dev.platform_data;
	struct iio_dev *indio_dev;
	struct ad5791_state *st;
	int ret, pos_voltage_uv = 0, neg_voltage_uv = 0;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;
	st = iio_priv(indio_dev);
	st->reg_vdd = devm_regulator_get(&spi->dev, "vdd");
	if (!IS_ERR(st->reg_vdd)) {
		ret = regulator_enable(st->reg_vdd);
		if (ret)
			return ret;

		ret = regulator_get_voltage(st->reg_vdd);
		if (ret < 0)
			goto error_disable_reg_pos;

		pos_voltage_uv = ret;
	}

	st->reg_vss = devm_regulator_get(&spi->dev, "vss");
	if (!IS_ERR(st->reg_vss)) {
		ret = regulator_enable(st->reg_vss);
		if (ret)
			goto error_disable_reg_pos;

		ret = regulator_get_voltage(st->reg_vss);
		if (ret < 0)
			goto error_disable_reg_neg;

		neg_voltage_uv = ret;
	}

	st->pwr_down = true;
	st->spi = spi;

	if (!IS_ERR(st->reg_vss) && !IS_ERR(st->reg_vdd)) {
		st->vref_mv = (pos_voltage_uv + neg_voltage_uv) / 1000;
		st->vref_neg_mv = neg_voltage_uv / 1000;
	} else if (pdata) {
		st->vref_mv = pdata->vref_pos_mv + pdata->vref_neg_mv;
		st->vref_neg_mv = pdata->vref_neg_mv;
	} else {
		dev_warn(&spi->dev, "reference voltage unspecified\n");
	}

	ret = ad5791_spi_write(st, AD5791_ADDR_SW_CTRL, AD5791_SWCTRL_RESET);
	if (ret)
		goto error_disable_reg_neg;

	st->chip_info =	&ad5791_chip_info_tbl[spi_get_device_id(spi)
					      ->driver_data];


	st->ctrl = AD5761_CTRL_LINCOMP(st->chip_info->get_lin_comp(st->vref_mv))
		  | ((pdata && pdata->use_rbuf_gain2) ? 0 : AD5791_CTRL_RBUF) |
		  AD5791_CTRL_BIN2SC;

	ret = ad5791_spi_write(st, AD5791_ADDR_CTRL, st->ctrl |
		AD5791_CTRL_OPGND | AD5791_CTRL_DACTRI);
	if (ret)
		goto error_disable_reg_neg;

	spi_set_drvdata(spi, indio_dev);
	indio_dev->dev.parent = &spi->dev;
	indio_dev->info = &ad5791_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels
		= &ad5791_channels[spi_get_device_id(spi)->driver_data];
	indio_dev->num_channels = 1;
	indio_dev->name = spi_get_device_id(st->spi)->name;
	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_disable_reg_neg;

	return 0;

error_disable_reg_neg:
	if (!IS_ERR(st->reg_vss))
		regulator_disable(st->reg_vss);
error_disable_reg_pos:
	if (!IS_ERR(st->reg_vdd))
		regulator_disable(st->reg_vdd);
	return ret;
}
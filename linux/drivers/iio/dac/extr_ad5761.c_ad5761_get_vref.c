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
struct ad5761_state {int use_intref; int vref; int /*<<< orphan*/ * vref_reg; TYPE_1__* spi; } ;
struct ad5761_chip_info {int int_vref; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * devm_regulator_get_optional (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ *) ; 
 int regulator_enable (int /*<<< orphan*/ *) ; 
 int regulator_get_voltage (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad5761_get_vref(struct ad5761_state *st,
			   const struct ad5761_chip_info *chip_info)
{
	int ret;

	st->vref_reg = devm_regulator_get_optional(&st->spi->dev, "vref");
	if (PTR_ERR(st->vref_reg) == -ENODEV) {
		/* Use Internal regulator */
		if (!chip_info->int_vref) {
			dev_err(&st->spi->dev,
				"Voltage reference not found\n");
			return -EIO;
		}

		st->use_intref = true;
		st->vref = chip_info->int_vref;
		return 0;
	}

	if (IS_ERR(st->vref_reg)) {
		dev_err(&st->spi->dev,
			"Error getting voltage reference regulator\n");
		return PTR_ERR(st->vref_reg);
	}

	ret = regulator_enable(st->vref_reg);
	if (ret) {
		dev_err(&st->spi->dev,
			 "Failed to enable voltage reference\n");
		return ret;
	}

	ret = regulator_get_voltage(st->vref_reg);
	if (ret < 0) {
		dev_err(&st->spi->dev,
			 "Failed to get voltage reference value\n");
		goto disable_regulator_vref;
	}

	if (ret < 2000000 || ret > 3000000) {
		dev_warn(&st->spi->dev,
			 "Invalid external voltage ref. value %d uV\n", ret);
		ret = -EIO;
		goto disable_regulator_vref;
	}

	st->vref = ret / 1000;
	st->use_intref = false;

	return 0;

disable_regulator_vref:
	regulator_disable(st->vref_reg);
	st->vref_reg = NULL;
	return ret;
}
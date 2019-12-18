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
struct regulator_config {int /*<<< orphan*/  dev; int /*<<< orphan*/  ena_gpiod; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg; } ;
struct da9055_regulator_info {TYPE_1__ conf; } ;
struct da9055_regulator {int reg_rselect; int /*<<< orphan*/  da9055; struct da9055_regulator_info* info; } ;
struct da9055_pdata {int* gpio_ren; int* reg_ren; int* gpio_rsel; int* reg_rsel; int /*<<< orphan*/ * ena_gpiods; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9055_E_GPI_MASK ; 
 int DA9055_E_GPI_SHIFT ; 
 int /*<<< orphan*/  DA9055_V_GPI_MASK ; 
 int DA9055_V_GPI_SHIFT ; 
 int /*<<< orphan*/  GPIOF_DIR_IN ; 
 int da9055_reg_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int devm_gpio_request_one (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int da9055_gpio_init(struct da9055_regulator *regulator,
			    struct regulator_config *config,
			    struct da9055_pdata *pdata, int id)
{
	struct da9055_regulator_info *info = regulator->info;
	int ret = 0;

	if (!pdata)
		return 0;

	if (pdata->gpio_ren && pdata->gpio_ren[id]) {
		char name[18];
		int gpio_mux = pdata->gpio_ren[id];

		config->ena_gpiod = pdata->ena_gpiods[id];

		/*
		 * GPI pin is muxed with regulator to control the
		 * regulator state.
		 */
		sprintf(name, "DA9055 GPI %d", gpio_mux);
		ret = devm_gpio_request_one(config->dev, gpio_mux, GPIOF_DIR_IN,
					    name);
		if (ret < 0)
			goto err;

		/*
		 * Let the regulator know that its state is controlled
		 * through GPI.
		 */
		ret = da9055_reg_update(regulator->da9055, info->conf.reg,
					DA9055_E_GPI_MASK,
					pdata->reg_ren[id]
					<< DA9055_E_GPI_SHIFT);
		if (ret < 0)
			goto err;
	}

	if (pdata->gpio_rsel && pdata->gpio_rsel[id]) {
		char name[18];
		int gpio_mux = pdata->gpio_rsel[id];

		regulator->reg_rselect = pdata->reg_rsel[id];

		/*
		 * GPI pin is muxed with regulator to select the
		 * regulator register set A/B for voltage ramping.
		 */
		sprintf(name, "DA9055 GPI %d", gpio_mux);
		ret = devm_gpio_request_one(config->dev, gpio_mux, GPIOF_DIR_IN,
					    name);
		if (ret < 0)
			goto err;

		/*
		 * Let the regulator know that its register set A/B
		 * will be selected through GPI for voltage ramping.
		 */
		ret = da9055_reg_update(regulator->da9055, info->conf.reg,
					DA9055_V_GPI_MASK,
					pdata->reg_rsel[id]
					<< DA9055_V_GPI_SHIFT);
	}

err:
	return ret;
}
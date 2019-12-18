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
struct twl_regulator_driver_data {unsigned long features; int /*<<< orphan*/ * data; int /*<<< orphan*/ * get_voltage; int /*<<< orphan*/ * set_voltage; } ;
struct regulator_init_data {unsigned int num_consumer_supplies; struct twl_regulator_driver_data* driver_data; struct regulator_consumer_supply* consumer_supplies; } ;
struct regulator_consumer_supply {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL_MODULE_PM_MASTER ; 
 struct device* add_numbered_child (int /*<<< orphan*/ ,char*,int,struct regulator_init_data*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct device *
add_regulator_linked(int num, struct regulator_init_data *pdata,
		struct regulator_consumer_supply *consumers,
		unsigned num_consumers, unsigned long features)
{
	struct twl_regulator_driver_data drv_data;

	/* regulator framework demands init_data ... */
	if (!pdata)
		return NULL;

	if (consumers) {
		pdata->consumer_supplies = consumers;
		pdata->num_consumer_supplies = num_consumers;
	}

	if (pdata->driver_data) {
		/* If we have existing drv_data, just add the flags */
		struct twl_regulator_driver_data *tmp;
		tmp = pdata->driver_data;
		tmp->features |= features;
	} else {
		/* add new driver data struct, used only during init */
		drv_data.features = features;
		drv_data.set_voltage = NULL;
		drv_data.get_voltage = NULL;
		drv_data.data = NULL;
		pdata->driver_data = &drv_data;
	}

	/* NOTE:  we currently ignore regulator IRQs, e.g. for short circuits */
	return add_numbered_child(TWL_MODULE_PM_MASTER, "twl_reg", num,
		pdata, sizeof(*pdata), false, 0, 0);
}
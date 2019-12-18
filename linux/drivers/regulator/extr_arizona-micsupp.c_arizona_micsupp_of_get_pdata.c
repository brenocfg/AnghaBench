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
struct regulator_init_data {int num_consumer_supplies; int /*<<< orphan*/ * consumer_supplies; } ;
struct regulator_desc {int dummy; } ;
struct regulator_config {TYPE_1__* dev; struct device_node* of_node; struct arizona_micsupp* driver_data; } ;
struct device_node {int dummy; } ;
struct arizona_micsupp_pdata {struct regulator_init_data* init_data; } ;
struct arizona_micsupp {int /*<<< orphan*/  supply; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 struct regulator_init_data* of_get_regulator_init_data (TYPE_1__*,struct device_node*,struct regulator_desc const*) ; 

__attribute__((used)) static int arizona_micsupp_of_get_pdata(struct arizona_micsupp_pdata *pdata,
					struct regulator_config *config,
					const struct regulator_desc *desc)
{
	struct arizona_micsupp *micsupp = config->driver_data;
	struct device_node *np;
	struct regulator_init_data *init_data;

	np = of_get_child_by_name(config->dev->of_node, "micvdd");

	if (np) {
		config->of_node = np;

		init_data = of_get_regulator_init_data(config->dev, np, desc);

		if (init_data) {
			init_data->consumer_supplies = &micsupp->supply;
			init_data->num_consumer_supplies = 1;

			pdata->init_data = init_data;
		}
	}

	return 0;
}
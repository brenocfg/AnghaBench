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
struct regulator_bulk_devres {int num_consumers; struct regulator_bulk_data* consumers; } ;
struct regulator_bulk_data {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_regulator_bulk_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct regulator_bulk_devres*) ; 
 struct regulator_bulk_devres* devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct regulator_bulk_devres*) ; 
 int regulator_bulk_get (struct device*,int,struct regulator_bulk_data*) ; 

int devm_regulator_bulk_get(struct device *dev, int num_consumers,
			    struct regulator_bulk_data *consumers)
{
	struct regulator_bulk_devres *devres;
	int ret;

	devres = devres_alloc(devm_regulator_bulk_release,
			      sizeof(*devres), GFP_KERNEL);
	if (!devres)
		return -ENOMEM;

	ret = regulator_bulk_get(dev, num_consumers, consumers);
	if (!ret) {
		devres->consumers = consumers;
		devres->num_consumers = num_consumers;
		devres_add(dev, devres);
	} else {
		devres_free(devres);
	}

	return ret;
}
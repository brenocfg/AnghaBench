#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct TYPE_5__ {scalar_t__ driver_data; int /*<<< orphan*/  of_node; int /*<<< orphan*/  init_data; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* ab3100_reg_init_order ; 
 int /*<<< orphan*/ * ab3100_reg_initvals ; 
 TYPE_1__* ab3100_regulator_matches ; 
 int ab3100_regulator_register (struct platform_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int abx500_set_register_interruptible (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
ab3100_regulator_of_probe(struct platform_device *pdev, struct device_node *np)
{
	int err, i;

	/*
	 * Set up the regulator registers, as was previously done with
	 * platform data.
	 */
	/* Set up regulators */
	for (i = 0; i < ARRAY_SIZE(ab3100_reg_init_order); i++) {
		err = abx500_set_register_interruptible(&pdev->dev, 0,
					ab3100_reg_init_order[i],
					ab3100_reg_initvals[i]);
		if (err) {
			dev_err(&pdev->dev, "regulator initialization failed with error %d\n",
				err);
			return err;
		}
	}

	for (i = 0; i < ARRAY_SIZE(ab3100_regulator_matches); i++) {
		err = ab3100_regulator_register(
			pdev, NULL, ab3100_regulator_matches[i].init_data,
			ab3100_regulator_matches[i].of_node,
			(unsigned long)ab3100_regulator_matches[i].driver_data);
		if (err)
			return err;
	}

	return 0;
}
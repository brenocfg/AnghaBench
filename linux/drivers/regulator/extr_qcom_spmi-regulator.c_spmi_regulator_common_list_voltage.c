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
struct spmi_regulator {TYPE_2__* set_points; } ;
struct regulator_dev {int dummy; } ;
struct TYPE_4__ {unsigned int n_voltages; int count; TYPE_1__* range; } ;
struct TYPE_3__ {unsigned int n_voltages; unsigned int step_uV; unsigned int set_point_min_uV; } ;

/* Variables and functions */
 struct spmi_regulator* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int spmi_regulator_common_list_voltage(struct regulator_dev *rdev,
			unsigned selector)
{
	struct spmi_regulator *vreg = rdev_get_drvdata(rdev);
	int uV = 0;
	int i;

	if (selector >= vreg->set_points->n_voltages)
		return 0;

	for (i = 0; i < vreg->set_points->count; i++) {
		if (selector < vreg->set_points->range[i].n_voltages) {
			uV = selector * vreg->set_points->range[i].step_uV
				+ vreg->set_points->range[i].set_point_min_uV;
			break;
		}

		selector -= vreg->set_points->range[i].n_voltages;
	}

	return uV;
}
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
struct regulator_bulk_data {int ret; int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int regulator_force_disable (int /*<<< orphan*/ ) ; 

int regulator_bulk_force_disable(int num_consumers,
			   struct regulator_bulk_data *consumers)
{
	int i;
	int ret = 0;

	for (i = 0; i < num_consumers; i++) {
		consumers[i].ret =
			    regulator_force_disable(consumers[i].consumer);

		/* Store first error for reporting */
		if (consumers[i].ret && !ret)
			ret = consumers[i].ret;
	}

	return ret;
}
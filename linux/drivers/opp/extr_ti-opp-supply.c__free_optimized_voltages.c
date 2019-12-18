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
struct ti_opp_supply_data {scalar_t__ num_vdd_table; int /*<<< orphan*/ * vdd_table; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _free_optimized_voltages(struct device *dev,
				     struct ti_opp_supply_data *data)
{
	kfree(data->vdd_table);
	data->vdd_table = NULL;
	data->num_vdd_table = 0;
}
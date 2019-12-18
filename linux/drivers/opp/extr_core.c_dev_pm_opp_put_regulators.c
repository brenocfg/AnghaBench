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
struct opp_table {int regulator_count; int /*<<< orphan*/ * regulators; int /*<<< orphan*/  opp_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  _free_set_opp_data (struct opp_table*) ; 
 int /*<<< orphan*/  dev_pm_opp_put_opp_table (struct opp_table*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ ) ; 

void dev_pm_opp_put_regulators(struct opp_table *opp_table)
{
	int i;

	if (!opp_table->regulators)
		goto put_opp_table;

	/* Make sure there are no concurrent readers while updating opp_table */
	WARN_ON(!list_empty(&opp_table->opp_list));

	for (i = opp_table->regulator_count - 1; i >= 0; i--)
		regulator_put(opp_table->regulators[i]);

	_free_set_opp_data(opp_table);

	kfree(opp_table->regulators);
	opp_table->regulators = NULL;
	opp_table->regulator_count = -1;

put_opp_table:
	dev_pm_opp_put_opp_table(opp_table);
}
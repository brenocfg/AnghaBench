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
struct opp_table {int required_opp_count; struct opp_table** required_opp_tables; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct opp_table*) ; 
 int /*<<< orphan*/  dev_pm_opp_put_opp_table (struct opp_table*) ; 
 int /*<<< orphan*/  kfree (struct opp_table**) ; 

__attribute__((used)) static void _opp_table_free_required_tables(struct opp_table *opp_table)
{
	struct opp_table **required_opp_tables = opp_table->required_opp_tables;
	int i;

	if (!required_opp_tables)
		return;

	for (i = 0; i < opp_table->required_opp_count; i++) {
		if (IS_ERR_OR_NULL(required_opp_tables[i]))
			break;

		dev_pm_opp_put_opp_table(required_opp_tables[i]);
	}

	kfree(required_opp_tables);

	opp_table->required_opp_count = 0;
	opp_table->required_opp_tables = NULL;
}
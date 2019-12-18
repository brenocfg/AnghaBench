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
struct opp_table {scalar_t__ regulator_count; } ;
struct dev_pm_opp_supply {int dummy; } ;
struct dev_pm_opp {int /*<<< orphan*/  node; struct dev_pm_opp_supply* supplies; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct dev_pm_opp* kzalloc (int,int /*<<< orphan*/ ) ; 

struct dev_pm_opp *_opp_allocate(struct opp_table *table)
{
	struct dev_pm_opp *opp;
	int count, supply_size;

	/* Allocate space for at least one supply */
	count = table->regulator_count > 0 ? table->regulator_count : 1;
	supply_size = sizeof(*opp->supplies) * count;

	/* allocate new OPP node and supplies structures */
	opp = kzalloc(sizeof(*opp) + supply_size, GFP_KERNEL);
	if (!opp)
		return NULL;

	/* Put the supplies at the end of the OPP structure as an empty array */
	opp->supplies = (struct dev_pm_opp_supply *)(opp + 1);
	INIT_LIST_HEAD(&opp->node);

	return opp;
}
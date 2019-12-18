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
struct opp_table {int required_opp_count; int /*<<< orphan*/  is_genpd; struct opp_table** required_opp_tables; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct opp_table*) ; 
 struct opp_table* _find_table_of_opp_np (struct device_node*) ; 
 int /*<<< orphan*/  _opp_table_free_required_tables (struct opp_table*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct opp_table** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int of_count_phandle_with_args (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* of_get_next_available_child (struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_required_opp (struct device_node*,int) ; 

__attribute__((used)) static void _opp_table_alloc_required_tables(struct opp_table *opp_table,
					     struct device *dev,
					     struct device_node *opp_np)
{
	struct opp_table **required_opp_tables;
	struct device_node *required_np, *np;
	int count, i;

	/* Traversing the first OPP node is all we need */
	np = of_get_next_available_child(opp_np, NULL);
	if (!np) {
		dev_err(dev, "Empty OPP table\n");
		return;
	}

	count = of_count_phandle_with_args(np, "required-opps", NULL);
	if (!count)
		goto put_np;

	required_opp_tables = kcalloc(count, sizeof(*required_opp_tables),
				      GFP_KERNEL);
	if (!required_opp_tables)
		goto put_np;

	opp_table->required_opp_tables = required_opp_tables;
	opp_table->required_opp_count = count;

	for (i = 0; i < count; i++) {
		required_np = of_parse_required_opp(np, i);
		if (!required_np)
			goto free_required_tables;

		required_opp_tables[i] = _find_table_of_opp_np(required_np);
		of_node_put(required_np);

		if (IS_ERR(required_opp_tables[i]))
			goto free_required_tables;

		/*
		 * We only support genpd's OPPs in the "required-opps" for now,
		 * as we don't know how much about other cases. Error out if the
		 * required OPP doesn't belong to a genpd.
		 */
		if (!required_opp_tables[i]->is_genpd) {
			dev_err(dev, "required-opp doesn't belong to genpd: %pOF\n",
				required_np);
			goto free_required_tables;
		}
	}

	goto put_np;

free_required_tables:
	_opp_table_free_required_tables(opp_table);
put_np:
	of_node_put(np);
}
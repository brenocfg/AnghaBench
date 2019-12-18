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
typedef  int /*<<< orphan*/  u32 ;
struct opp_table {int is_genpd; struct device_node* np; int /*<<< orphan*/  shared_opp; int /*<<< orphan*/  voltage_tolerance_v1; int /*<<< orphan*/  clock_latency_ns_max; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPP_TABLE_ACCESS_EXCLUSIVE ; 
 int /*<<< orphan*/  OPP_TABLE_ACCESS_SHARED ; 
 struct device_node* _opp_of_get_opp_desc_node (struct device_node*,int) ; 
 int /*<<< orphan*/  _opp_table_alloc_required_tables (struct opp_table*,struct device*,struct device_node*) ; 
 scalar_t__ of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* of_node_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

void _of_init_opp_table(struct opp_table *opp_table, struct device *dev,
			int index)
{
	struct device_node *np, *opp_np;
	u32 val;

	/*
	 * Only required for backward compatibility with v1 bindings, but isn't
	 * harmful for other cases. And so we do it unconditionally.
	 */
	np = of_node_get(dev->of_node);
	if (!np)
		return;

	if (!of_property_read_u32(np, "clock-latency", &val))
		opp_table->clock_latency_ns_max = val;
	of_property_read_u32(np, "voltage-tolerance",
			     &opp_table->voltage_tolerance_v1);

	if (of_find_property(np, "#power-domain-cells", NULL))
		opp_table->is_genpd = true;

	/* Get OPP table node */
	opp_np = _opp_of_get_opp_desc_node(np, index);
	of_node_put(np);

	if (!opp_np)
		return;

	if (of_property_read_bool(opp_np, "opp-shared"))
		opp_table->shared_opp = OPP_TABLE_ACCESS_SHARED;
	else
		opp_table->shared_opp = OPP_TABLE_ACCESS_EXCLUSIVE;

	opp_table->np = opp_np;

	_opp_table_alloc_required_tables(opp_table, dev, opp_np);
	of_node_put(opp_np);
}
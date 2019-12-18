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
struct opp_table {scalar_t__ np; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int _of_add_opp_table_v1 (struct device*,struct opp_table*) ; 
 int _of_add_opp_table_v2 (struct device*,struct opp_table*) ; 
 struct opp_table* dev_pm_opp_get_opp_table_indexed (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_opp_put_opp_table (struct opp_table*) ; 

int dev_pm_opp_of_add_table(struct device *dev)
{
	struct opp_table *opp_table;
	int ret;

	opp_table = dev_pm_opp_get_opp_table_indexed(dev, 0);
	if (!opp_table)
		return -ENOMEM;

	/*
	 * OPPs have two version of bindings now. Also try the old (v1)
	 * bindings for backward compatibility with older dtbs.
	 */
	if (opp_table->np)
		ret = _of_add_opp_table_v2(dev, opp_table);
	else
		ret = _of_add_opp_table_v1(dev, opp_table);

	if (ret)
		dev_pm_opp_put_opp_table(opp_table);

	return ret;
}
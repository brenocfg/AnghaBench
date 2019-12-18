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
struct opp_table {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int _of_add_opp_table_v2 (struct device*,struct opp_table*) ; 
 struct opp_table* dev_pm_opp_get_opp_table_indexed (struct device*,int) ; 
 int /*<<< orphan*/  dev_pm_opp_put_opp_table (struct opp_table*) ; 
 int of_count_phandle_with_args (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

int dev_pm_opp_of_add_table_indexed(struct device *dev, int index)
{
	struct opp_table *opp_table;
	int ret, count;

	if (index) {
		/*
		 * If only one phandle is present, then the same OPP table
		 * applies for all index requests.
		 */
		count = of_count_phandle_with_args(dev->of_node,
						   "operating-points-v2", NULL);
		if (count == 1)
			index = 0;
	}

	opp_table = dev_pm_opp_get_opp_table_indexed(dev, index);
	if (!opp_table)
		return -ENOMEM;

	ret = _of_add_opp_table_v2(dev, opp_table);
	if (ret)
		dev_pm_opp_put_opp_table(opp_table);

	return ret;
}